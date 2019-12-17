CC              := clang
CFLAGS          := -Wall -Wextra -Werror -Wunused -MMD
CFLAGS_DEBUG    := -glldb -Og
CFLAGS_SANITIZE := $(CFLAGS_DEBUG) -fsanitize=address
CFLAGS_OPTIMIZE := -march=native -mtune=native -Ofast -pipe -flto -fpic
CFLAGS_ASSEMBLY := $(filter-out -flto -fpic,$(CFLAGS_OPTIMIZE)) -S -masm=intel
CFLAGS_OPTIONAL := $(CFLAGS_OPTIMIZE)

# all header .h files must be placed in to "includes" folder(or sub-dirs) only.
ifneq (,$(wildcard ./includes))
IFLAGS := $(addprefix -I,$(shell find ./includes -type d))
else
$(error "all header .h files must be placed in to "includes" folder(or sub-dirs) only.")
endif
