.EXPORT_ALL_VARIABLES:

NAME := libtpool.a
NPWD := $(CURDIR)/$(NAME)

# all source code .c files must to places in to "srcs" folder(or sub-dirs) only.
ifneq (,$(wildcard ./srcs))
SRCS := $(shell find srcs -name "*.c")
OBJS := $(SRCS:.c=.o)
ASMS :=
else
$(error "all source code .c files must to places in to "srcs" folder(or sub-dirs) only.")
endif
