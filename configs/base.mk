NAME := libft.a
NPWD := $(CURDIR)/$(NAME)

CC     := clang

# all .c files must to placed in to "srcs" folder(or sub-dirs) only.
ifneq (,$(wildcard ./srcs))
SRCS      := $(shell find srcs -name "*.c")
OBJS      := $(SRCS:.c=.o)
endif

DEL  := rm -rf
