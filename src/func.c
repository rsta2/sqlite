//
// func.c
//
// Unresolved externals in sqlite3.c and shell.c
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>

int access (const char *pathname, int mode)
{
	printf ("access(\"%s\", %d)\n", pathname, mode);

	errno = EACCES;

	return -1;
}

int chdir (const char *pathname)
{
	printf ("chdir()\n");

	errno = EACCES;

	return -1;
}

int chmod (const char *pathname, mode_t mode)
{
	printf ("chmod()\n");

	errno = EACCES;

	return -1;
}

struct passwd *getpwuid (uid_t uid)
{
	printf ("getpwuid(%d)\n", uid);

	static struct passwd pw;
	pw.pw_name = "sqlite";
	pw.pw_passwd = "";
	pw.pw_uid = uid;
	pw.pw_gid = 100;
	pw.pw_gecos = "SQLite user";
	pw.pw_dir = "SD:/";
	pw.pw_shell = "";

	return &pw;
}

struct rusage {};
int getrusage (int who, struct rusage *usage)
{
	printf ("getrusage()\n");

	errno = EINVAL;

	return -1;
}

uid_t getuid (void)
{
	return 100;
}

uid_t geteuid (void)
{
	return 100;
}

FILE *popen (const char *command, const char *type)
{
	printf ("popen()\n");

	errno = EINVAL;

	return NULL;
}

int pclose (FILE *stream)
{
	printf ("pclose()\n");

	errno = EINVAL;

	return -1;
}

ssize_t readlink (const char *pathname, char *buffer, size_t bufsize)
{
	printf ("readlink()\n");

	errno = EACCES;

	return -1;
}

int symlink (const char *target, const char *linkpath)
{
	printf ("symlink()\n");

	errno = EACCES;

	return -1;
}

int utimes(const char *filename, const struct timeval times[2])
{
	printf ("utimes()\n");

	errno = EACCES;

	return -1;
}

unsigned sleep (unsigned seconds)
{
	printf ("sleep(%d)\n", seconds);

	return 0;
}

int fsync (int dd)
{
	printf ("fsync(%d)\n", dd);

	return 0;
}

char *getcwd (char *buffer, size_t size)
{
	printf ("getcwd()\n");

	strncpy (buffer, "SD:/", size);

	if (size > 0)
	{
		buffer[size-1] = '\0';
	}

	return buffer;
}

int ftruncate (int fd, off_t length)
{
	printf ("ftruncate()\n");

	errno = EINVAL;

	return -1;
}

int fchmod (int fd, mode_t mode)
{
	printf ("fchmod()\n");

	errno = EACCES;

	return -1;
}

int rmdir (const char *pathname)
{
	printf ("rmdir()\n");

	errno = EACCES;

	return -1;
}

int fchown(int fd, uid_t owner, gid_t group)
{
	printf ("fchmod()\n");

	errno = EACCES;

	return -1;
}
