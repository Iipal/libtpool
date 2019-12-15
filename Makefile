include configs/default_lib_config.mk

.PHONY: all multi STATUS_START
multi: STATUS_START
 ifneq (,$(filter $(MAKECMDGOALS),debug debug_all))
	@$(MAKE) $(MAKE_PARALLEL_FLAGS) CFLAGS_OPTIONAL="$(CFLAGS_DEBUG)" \
		DEFINES="$(shell echo $(basename $(NAME)) | tr a-z A-Z)_DEBUG" all
 else ifneq (,$(filter $(MAKECMDGOALS),sanitize sanitize_all))
	@$(MAKE) $(MAKE_PARALLEL_FLAGS) CFLAGS_OPTIONAL="$(CFLAGS_SANITIZE)" \
		DEFINES="$(shell echo $(basename $(NAME)) | tr a-z A-Z)_SANITIZE" all
 else ifneq (,$(filter $(MAKECMDGOALS),assembly assembly_all))
	@$(MAKE) $(MAKE_PARALLEL_FLAGS) CFLAGS_OPTIONAL="$(CFLAGS_ASSEMBLY)" ASSEMBLY_FLAG=1 \
		DEFINES="$(shell echo $(basename $(NAME)) | tr a-z A-Z)_ASSEMBLY" all
 else ifneq (,$(filter $(MAKECMDGOALS),llvm_assembly llvm_assembly_all))
	@$(MAKE) $(MAKE_PARALLEL_FLAGS) CFLAGS_OPTIONAL="$(CFLAGS_LLVM_ASSEMBLY)" ASSEMBLY_FLAG=2 \
		DEFINES="$(shell echo $(basename $(NAME)) | tr a-z A-Z)_LLVM_ASSEMBLY" all
 else
	@$(MAKE) $(MAKE_PARALLEL_FLAGS) all
 endif

STATUS_START:
	@$(ECHO) " | -------"
	@$(ECHO) " | making: $(CLR_UNDERLINE)$(NAME)$(CLR_WHITE) ..."
	@$(ECHO) " | -------"

all: $(NAME)

$(NAME): $(OBJS) $(ASMS) $(LLVM_ASMS)
 ifeq (0,$(ASSEMBLY_FLAG))
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
 endif
	@$(MAKE) STATUS

-include $(DEPS)
$(OBJS): %.o: %.c
 ifeq (0,$(ASSEMBLY_FLAG))
	@$(CC) $(addprefix -D,$(DEFINES)) -c $(CFLAGS) $(CFLAGS_OPTIONAL) $(IFLAGS) $< -o $@
	@$(ECHO) " | $@: $(MSG_SUCCESS)"
 endif

$(ASMS): %.s: %.c
 ifeq (1,$(ASSEMBLY_FLAG))
	@$(CC) $(addprefix -D,$(DEFINES)) -c $(CFLAGS) $(CFLAGS_OPTIONAL) $(IFLAGS) $< -o $(basename $@).s
	@$(ECHO) " | $(basename $@).s: $(MSG_SUCCESS)"
 endif

$(LLVM_ASMS): %.ll: %.c
 ifeq (2,$(ASSEMBLY_FLAG))
	@$(CC) $(addprefix -D,$(DEFINES)) -c $(CFLAGS) $(CFLAGS_OPTIONAL) $(IFLAGS) $< -o $(basename $@).ll
	@$(ECHO) " | $(basename $@).ll: $(MSG_SUCCESS)"
 endif

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

clean:
	@$(DEL) $(OBJS)
	@$(DEL) $(DEPS)
	@$(DEL) $(ASMS)
	@$(DEL) $(LLVM_ASMS)
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

.PHONY: re fclean clean norme del pre sanitize sanitize_all debug debug_all STATUS
