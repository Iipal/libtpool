CC		:=	clang
CFLAGS	:=	-Wall -Wextra -Werror -I $(CURDIR)/includes
LDFLAGS	:=	-pthread

SOURCES	:=	$(CURDIR)/srcs/tpool/tpool_add_work.c \
			$(CURDIR)/srcs/tpool/tpool_create.c \
			$(CURDIR)/srcs/tpool/tpool_destroy.c \
			$(CURDIR)/srcs/tpool/tpool_wait.c \
			$(CURDIR)/Example.c

OBJECTS	:=	$(SOURCES:.c=.o)

NAME	:=	Example

all: $(CURDIR)/$(NAME)

$(CURDIR)/$(NAME): $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
