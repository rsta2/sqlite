//
// func.c
//
// by Rene Stange, Public Domain
//
// In this file the functions are implemented, which are used by sqlite3.c
// and shell.c and are not or not sufficiently provided by circle-newlib.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <fatfs/ff.h>
#include <assert.h>

#define SQLITE_HOME		"/sqlite"

#define SQLITE_PID		1000
#define SQLITE_UID		0
#define SQLITE_GID		0

#define SQLITE_MAX_PATH		512
#define SQLITE_MAX_FILES	20

static char filename[SQLITE_MAX_FILES][SQLITE_MAX_PATH+1];

int myinit (void)
{
        if (chdir (SQLITE_HOME) < 0)
	{
		printf ("Cannot chdir to %s.\n", SQLITE_HOME);

		return -1;
	}

	return 0;
}

// Save the pathname of an opened file. We need this for myfstat(), because
// it is called with a file descriptor, but we need the filename.
int myopen (const char *pathname, int flags, int mode)
{
	assert (pathname);
	int fd = open (pathname, flags, mode);
	if (fd < 0)
	{
		return fd;
	}

	if (   fd >= SQLITE_MAX_FILES
	    || pathname[0] != '/'		// SQLite calls this with an absolute path.
	    || strlen (pathname) > SQLITE_MAX_PATH)
	{
		close (fd);

		errno = ENFILE;

		return -1;
	}

	strcpy (filename[fd], pathname);

	return fd;
}

// Currently this wrapper is not needed, but if we need
// some additional processing on close() later.
int myclose (int fd)
{
	return close (fd);
}

int myfstat (int fd, struct stat *statbuf)
{
	if (fd >= SQLITE_MAX_FILES)
	{
		errno = EBADF;

		return -1;
	}

	return stat (filename[fd], statbuf);
}

// There is no file record locking implemented.
// It is not known, where this could cause problems with SQLite.
int myfcntl (int fd, int cmd, struct flock *lock)
{
	if (cmd != F_SETLK)
	{
		errno = EINVAL;

		return -1;
	}

	return 0;
}

int access (const char *pathname, int mode)
{
	assert (pathname);
	FILINFO finfo;
	FRESULT fr = f_stat (pathname, &finfo);
	if (   fr != FR_OK
	    || (   (mode & W_OK)
	        && (finfo.fattrib & AM_RDO)))
	{
		errno = EACCES;

		return -1;
	}

	return 0;
}

int chmod (const char *pathname, mode_t mode)
{
	assert (pathname);
	FRESULT fr = f_chmod (pathname, mode & S_IWUSR ? 0 : AM_RDO, AM_RDO);
	if (fr != FR_OK)
	{
		errno = EACCES;

		return -1;
	}

	return 0;
}

struct passwd *getpwuid (uid_t uid)
{
	static struct passwd pw;

	pw.pw_name = "sqlite";
	pw.pw_passwd = "";
	pw.pw_uid = uid;
	pw.pw_gid = SQLITE_GID;
	pw.pw_gecos = "SQLite user";
	pw.pw_dir = SQLITE_HOME;
	pw.pw_shell = "";

	return &pw;
}

int getrusage (int who, struct rusage *usage)
{
	assert (usage);
	memset (usage, 0, sizeof *usage);

	return 0;
}

int getpid (void)
{
	return SQLITE_PID;
}

uid_t getuid (void)
{
	return SQLITE_UID;
}

uid_t geteuid (void)
{
	return SQLITE_UID;
}

FILE *popen (const char *command, const char *type)
{
	errno = EINVAL;

	return NULL;
}

int pclose (FILE *stream)
{
	errno = ECHILD;

	return -1;
}

ssize_t readlink (const char *pathname, char *buffer, size_t bufsize)
{
	errno = EINVAL;

	return -1;
}

int symlink (const char *target, const char *linkpath)
{
	errno = EPERM;

	return -1;
}

int utimes (const char *pathname, const struct timeval *times)
{
	assert (pathname);
	assert (times);

	struct tm tm;
	if (localtime_r (&times[1].tv_sec, &tm) != &tm)
	{
		errno = EINVAL;

		return -1;
	}

	FILINFO finfo;
	finfo.fdate = (WORD) (((tm.tm_year - 80) * 512U) | (tm.tm_mon + 1) * 32U | tm.tm_mday);
	finfo.ftime = (WORD) (tm.tm_hour * 2048U | tm.tm_min * 32U | tm.tm_sec / 2U);

	FRESULT fr = f_utime (pathname, &finfo);
	if (fr != FR_OK)
	{
		errno = ENOENT;

		return -1;
	}

	return 0;
}

unsigned sleep (unsigned seconds)
{
	time_t t = time (NULL);

	while (time (NULL) - t < seconds)
	{
		// just wait
	}

	return 0;
}

// Cannot change the file mode on an open file.
int fchmod (int fd, mode_t mode)
{
	return 0;
}

int rmdir (const char *pathname)
{
	assert (pathname);
	FILINFO finfo;
	if (   f_stat (pathname, &finfo) != FR_OK
	    || !(finfo.fattrib & AM_DIR)
	    || f_unlink (pathname) != FR_OK)
	{
		errno = ENOENT;

		return -1;
	}

	return 0;
}

// FAT has not file owner info.
int fchown (int fd, uid_t owner, gid_t group)
{
	return 0;
}
