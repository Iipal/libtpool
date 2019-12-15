CFLAGS          := -Wall -Wextra -Werror -Wunused -MMD
CFLAGS_DEBUG    := -glldb -O0
CFLAGS_SANITIZE := $(CFLAGS_DEBUG) -Og -fsanitize=address
CFLAGS_OPTIMIZE := -march=native -mtune=native -Ofast -pipe -flto -fpic
CFLAGS_OPTIONAL := $(CFLAGS_OPTIMIZE)
ARFLAGS         := -rcs

# all .h files must to placed in to "includes" folder(or sub-dirs) only.
ifneq (,$(wildcard ./includes))
IFLAGS := $(addprefix -I,$(shell find ./includes -type d))
endif
