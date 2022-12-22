#
# Makefile
#

CIRCLESTDLIBHOME = ../circle-stdlib

include $(CIRCLESTDLIBHOME)/Config.mk

CIRCLEHOME = $(CIRCLESTDLIBHOME)/libs/circle
NEWLIBDIR = $(CIRCLESTDLIBHOME)/install/$(NEWLIB_ARCH)

OBJS	= main.o kernel.o func.o shell.o sqlite3.o

DEFINE += -DSQLITE_MUTEX_NOOP -DSQLITE_OMIT_WAL -DSQLITE_OMIT_LOAD_EXTENSION

#OPTIMIZE = -O0

include $(CIRCLEHOME)/Rules.mk

CFLAGS += -I "$(NEWLIBDIR)/include" -I $(STDDEF_INCPATH) -I $(CIRCLESTDLIBHOME)/include
LIBS := "$(NEWLIBDIR)/lib/libm.a" "$(NEWLIBDIR)/lib/libc.a" "$(NEWLIBDIR)/lib/libcirclenewlib.a" \
 	$(CIRCLEHOME)/addon/SDCard/libsdcard.a \
  	$(CIRCLEHOME)/lib/usb/libusb.a \
 	$(CIRCLEHOME)/lib/input/libinput.a \
 	$(CIRCLEHOME)/addon/fatfs/libfatfs.a \
 	$(CIRCLEHOME)/lib/fs/libfs.a \
  	$(CIRCLEHOME)/lib/net/libnet.a \
  	$(CIRCLEHOME)/lib/sched/libsched.a \
  	$(CIRCLEHOME)/lib/libcircle.a
