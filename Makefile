include configs/base.mk
include configs/flags.mk
include configs/os_dependency.mk
include configs/colors.mk

.PHONY: all multi STATUS_START
multi: STATUS_START
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
	@$(eval ASSEMBLY_FLAG:=1)
	@$(eval OBJS:=$(OBJS:.o=.S))
 endif
 ifneq (,$(filter $(MAKECMDGOALS),llvm_assembly llvm_assembly_all))
	@$(eval CFLAGS_OPTIONAL:=$(CFLAGS_LLVM_ASSEMBLY))
	@$(eval DEFINES:=$(shell echo $(basename $(NAME)) | tr a-z A-Z)_LLVM_ASSEMBLY)
	@$(eval ASSEMBLY_FLAG:=2)
	@$(eval OBJS:=$(OBJS:.o=.ll))
 endif
	@$(MAKE) -e $(MAKE_PARALLEL_FLAGS) all

STATUS_START:
 ifeq (,$(filter $(MAKECMDGOALS),assembly llvm_assembly assembly_all llvm_assembly_all))
	@$(ECHO) " | -------"
	@$(ECHO) " | making: $(CLR_UNDERLINE)$(NAME)$(CLR_WHITE) ..."
	@$(ECHO) " | -------"
 endif

all: $(NAME)

$(NAME): $(OBJS)
 ifeq (0,$(ASSEMBLY_FLAG))
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
 endif
	@$(MAKE) STATUS

-include $(SRCS:.c=.d)
$(OBJS): $(SRCS)
	@$(CC) $(addprefix -D,$(DEFINES)) \
		$(CFLAGS) $(CFLAGS_OPTIONAL) $(IFLAGS) \
		-c $< -o $@
	@$(ECHO) " | $@: $(MSG_SUCCESS)"

STATUS:
	@$(ECHO) "/ -------------------------"
 ifneq (,$(NAME))
  ifeq (0,$(ASSEMBLY_FLAG))
	@$(ECHO) "| compiled                : $(NAME) $(MSG_SUCCESS)"
  endif
 endif
 ifneq (,$(DEFINES))
	@$(ECHO) "| compiler custom defines : $(foreach dfns,$(DEFINES),$(CLR_INVERT)$(dfns)$(CLR_WHITE) )"
 endif
 ifneq (,$(CFLAGS))
	@$(ECHO) "| compiler          flags : $(CFLAGS)"
 endif
 ifneq (,$(CFLAGS_OPTIONAL))
	@$(ECHO) "| compiler optional flags : $(CLR_UNDERLINE)$(CFLAGS_OPTIONAL)$(CLR_WHITE)"
 endif
 ifneq (,$(ARFLAGS))
  ifeq (0,$(ASSEMBLY_FLAG))
	@$(ECHO) "| archiver          flags : $(CLR_UNDERLINE)$(ARFLAGS)$(CLR_WHITE)"
  endif
 endif
	@$(ECHO) "\\ -------------------------"

debug_all: pre
debug: multi

sanitize_all: pre
sanitize: multi

assembly_all: pre
assembly: multi

llvm_assembly_all: pre
llvm_assembly: multi

clean_llvm_assembly:
	@$(DEL) $(LLVM_ASMS)
clean_assembly:
	@$(DEL) $(ASMS)
clean_deps:
	@$(DEL) $(OBJS:%.o=%.d)
clean: clean_deps clean_assembly clean_llvm_assembly
	@$(DEL) $(OBJS)
	@$(ECHO) " | $(CLR_INVERT)deleted$(CLR_WHITE): $(NPWD) source objects"
fclean: clean
	@$(DEL) $(NAME)
	@$(ECHO) " | $(CLR_INVERT)deleted$(CLR_WHITE): $(NPWD)"

pre: fclean multi
re: fclean multi

norme:
	@$(ECHO) "$(CLR_INVERT)norminette$(CLR_WHITE) for $(NPWD):"
	@norminette includes/
	@norminette $(SRCS)

.PHONY: re fclean clean clean_assembly clean_llvm_assembly clean_deps assembly assembly_all llvm_assembly llvm_assembly_all norme del pre sanitize sanitize_all debug debug_all STATUS
.SUFFIXES:
.SUFFIXES: .o .S .ll .d
.EXPORT_ALL_VARIABLES:
