CFLAGS_DEBUG         := -glldb
CFLAGS_SANITIZE      := $(CFLAGS_DEBUG) -Og -fsanitize=thread
CFLAGS_OPTIMIZE      := -march=native -mtune=native -Ofast -pipe -flto -fpic
CFLAGS_ASSEMBLY      := $(filter-out -flto,$(CFLAGS_OPTIMIZE)) -S -masm=intel
CFLAGS_LLVM_ASSEMBLY := $(filter-out -masm=intel,$(CFLAGS_ASSEMBLY)) -emit-llvm

CFLAGS_OPTIONAL := $(CFLAGS_OPTIMIZE)

ARFLAGS := -rcs

ASSEMBLY_FLAG := 0
# 0 = no  assembly code generate
# 1 = .S  assembly
# 2 = .ll assembly
