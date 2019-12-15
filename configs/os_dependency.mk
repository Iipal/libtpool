ECHO    := echo
MAKE    := make
NPROCS  := 1
UNAME_S := $(shell uname -s)
# Linux Specifications:
ifeq ($(UNAME_S),Linux)
# Only for Red-Hat systems where -e param isn't enabled by default in echo built-in command.
# Remove this line if you have enabled -e option in echo command.
ECHO += -e

NPROCS              := $(shell grep -c ^processor /proc/cpuinfo)
MAKE_PARALLEL_FLAGS := -j $(NPROCS) -l $(NPROCS) -Otarget
AR                  := llvm-ar
endif

# MacOS Specifications:
ifeq ($(UNAME_S),Darwin)
# Only for MacOS where brew install path on home directory
#  or user don't have enought permissions to install latest version of GNUMake on system globally.
# Remove this line if in your MacOS system already installed GNUMake 4.0.0 or later.
 ifneq ($(wildcard ~/.brew/bin/gmake),)
	MAKE                := ~/.brew/bin/gmake
	NPROCS              := $(shell sysctl -n hw.ncpu)
	MAKE_PARALLEL_FLAGS := -j $(NPROCS) -l $(NPROCS) -Otarget
 endif

AR := ar
endif

MAKE += --no-print-directory
