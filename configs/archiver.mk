ARFLAGS := -rcs
AR      := ar
UNAME_S ?= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
AR := llvm-ar
endif
