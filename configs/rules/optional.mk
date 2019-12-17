make_optional:
 ifneq (,$(filter $(MAKECMDGOALS),debug debug_all))
	@$(eval CFLAGS_OPTIONAL:=$(CFLAGS_DEBUG))
	@$(eval DEFINES:=$(shell echo $(basename $(NAME)) | tr a-z A-Z)_DEBUG)
 endif
 ifneq (,$(filter $(MAKECMDGOALS),sanitize sanitize_all))
	@$(eval CFLAGS_OPTIONAL:=$(CFLAGS_SANITIZE))
	@$(eval DEFINES:=$(shell echo $(basename $(NAME)) | tr a-z A-Z)_SANITIZE)
 endif
 ifneq (,$(filter $(MAKECMDGOALS),assembly assembly_all))
	@$(eval CFLAGS_OPTIONAL:=$(CFLAGS_ASSEMBLY))
	@$(eval DEFINES:=$(shell echo $(basename $(NAME)) | tr a-z A-Z)_ASSEMBLY)
	@$(eval ASMS:=$(OBJS:.o=.S))
	@$(eval OBJS:=)
 endif

.PHONY: debug debug_all
debug_all: pre
debug: multi

.PHONY: sanitize sanitize_all
sanitize_all: pre
sanitize: multi

.PHONY: assembly assembly_all
assembly_all: pre
assembly: multi
