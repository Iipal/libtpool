NAME := libtpool.a
NPWD := $(CURDIR)/$(NAME)

CC     := clang
CFLAGS := -Wall -Wextra -Werror -Wunused -MMD

# all .h files must to placed in to "includes" folder(or sub-dirs) only.
ifneq (,$(wildcard ./includes))
IFLAGS := $(addprefix -I,$(shell find ./includes -type d))
endif

# all .c files must to placed in to "srcs" folder(or sub-dirs) only.
ifneq (,$(wildcard ./srcs))
SRCS      := $(shell find srcs -name "*.c")
OBJS      := $(SRCS:.c=.o)
ASMS      := $(SRCS:.c=.S)
LLVM_ASMS := $(SRCS:.c=.ll)
endif

DEL  := rm -rf
