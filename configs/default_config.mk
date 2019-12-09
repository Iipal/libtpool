NAME := $(notdir $(CURDIR))
NPWD := $(CURDIR)/$(NAME)

CC := clang

CFLAGS := -march=native -mtune=native -Ofast -pipe -flto -fpic
CFLAGS_DEBUG := -glldb -D DEBUG
CFLAGS_SANITIZE := -glldb -D DEBUG -fsanitize=address

CFLAGS_WARN := -Wall -Wextra -Werror -Wunused

IF_DIRS := $(shell find . -name "includes")
IF_SUBDIRS := $(foreach I_PATH,$(IF_DIRS),$(shell find $(I_PATH) -type d))
IFLAGS := $(addprefix -I,$(IF_DIRS)) $(addprefix -I,$(IF_SUBDIRS))

SRCS := $(shell find srcs -name "*.c")
OBJS := $(SRCS:.c=.o)

LIBS_DIRS := $(shell find ./libs -maxdepth 1 -type d)
LIBS_DIRS := $(filter-out $(firstword $(LIBS_DIRS)), $(LIBS_DIRS))
LIBS_NAMES = $(join $(LIBS_DIRS),$(addsuffix .a,$(addprefix /,$(notdir $(LIBS_DIRS)))))

ECHO := echo
MAKE := make
DEL := rm -rf

UNAME_S := $(shell uname -s)
# Linux Specifications:
ifeq ($(UNAME_S),Linux)
# Only for Red-Hat systems where -e param isn't enabled by default in echo built-in command.
# Remove this line if you have enabled -e option in echo command.
ECHO += -e

NPROCS := $(shell grep -c ^processor /proc/cpuinfo)
MAKE_PARALLEL_FLAGS := -j $(NPROCS) -l $(NPROCS) -Otarget
endif

# MacOS Specifications:
ifeq ($(UNAME_S),Darwin)
# Only for MacOS where brew install path on home directory
#  or user don't have enought permissions to install latest version of GNUMake on system globally.
# Remove this if in your MacOS system already installed GNUMake 4.0.0 or later.
ifneq ($(wildcard ~/.brew/bin/gmake),)
	MAKE := ~/.brew/bin/gmake
	NPROCS := $(shell sysctl -n hw.ncpu)
	MAKE_PARALLEL_FLAGS := -j $(NPROCS) -l $(NPROCS) -Otarget
endif

endif

MAKE += --no-print-directory

CLR_INVERT := \033[7m
CLR_UNDERLINE := \033[4m

CLR_GREEN := \033[32m
CLR_WHITE := \033[0m
CLR_BLUE := \033[34m

MSG_SUCCESS := [$(CLR_GREEN)✓$(CLR_WHITE)]
MSG_BSUCCESS := [$(CLR_BLUE)✓$(CLR_WHITE)]
MSG_SUCCESS_NO_CLR := [✓]
