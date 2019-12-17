.EXPORT_ALL_VARIABLES:

NAME := $(notdir $(CURDIR)).a
NPWD := $(CURDIR)/$(NAME)

# all source code .c files must to places in to "srcs" folder(or sub-dirs) only.
ifneq (,$(wildcard ./srcs))
SRCS := $(shell find srcs -name "*.c")
OBJS := $(SRCS:.c=.o)
ASMS := # reversed for 'assembly' and 'assembly_all' rules where ASMS:=$(SRCS:%.c=%.S) and OBJS:= equals to nothing
else
$(error "all source code .c files must to places in to "srcs" folder(or sub-dirs) only.")
endif
# all header .h files must be placed in to "includes" folder(or sub-dirs) only.
ifneq (,$(wildcard ./includes))
IFLAGS := $(addprefix -I,$(shell find ./includes -type d))
else
$(error "all header .h files must be placed in to "includes" folder(or sub-dirs) only.")
endif

CC              := clang
CFLAGS          := -Wall -Wextra -Werror -Wunused -MMD
CFLAGS_DEBUG    := -glldb -Og
CFLAGS_SANITIZE := $(CFLAGS_DEBUG) -fsanitize=address
CFLAGS_OPTIMIZE := -march=native -mtune=native -Ofast -pipe -flto -fpic
CFLAGS_ASSEMBLY := $(filter-out -flto -fpic,$(CFLAGS_OPTIMIZE)) -S -masm=intel

CFLAGS_OPTIONAL := $(CFLAGS_OPTIMIZE)

AR              := ar
ARFLAGS         := -rcs

UNAME_S ?= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
AR := llvm-ar
endif
