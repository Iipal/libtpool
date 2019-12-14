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
	@$(MAKE) $(MAKE_PARALLEL_FLAGS) CFLAGS_OPTIONAL="$(CFLAGS_ASSEMBLY)" ARFLAGS= \
		DEFINES="$(shell echo $(basename $(NAME)) | tr a-z A-Z)_ASSEMBLY" all
 else
	@$(MAKE) $(MAKE_PARALLEL_FLAGS) all
 endif

STATUS_START:
	@$(ECHO) " | -------"
	@$(ECHO) " | making: $(CLR_UNDERLINE)$(NAME)$(CLR_WHITE) ..."
	@$(ECHO) " | -------"

all: $(NAME)

$(NAME): $(OBJS) $(ASMS)
 ifneq (,$(ARFLAGS))
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
 endif
	@$(MAKE) STATUS

-include $(DEPS)
$(OBJS): %.o: %.c
 ifneq (,$(ARFLAGS))
	@$(CC) $(addprefix -D,$(DEFINES)) -c $(CFLAGS) $(CFLAGS_OPTIONAL) $(IFLAGS) $< -o $@
	@$(ECHO) " | $@: $(MSG_SUCCESS)"
 else
	@echo $< > /dev/null
 endif

$(ASMS): %.s: %.c
 ifeq (,$(ARFLAGS))
	@$(CC) $(addprefix -D,$(DEFINES)) -c $(CFLAGS) $(CFLAGS_OPTIONAL) $(IFLAGS) $< -o $(basename $@).s
	@$(ECHO) " | $(basename $@).s: $(MSG_SUCCESS)"
 endif

STATUS:
	@$(ECHO) "/ -------------------------"
 ifneq (,$(NAME))
  ifneq (,$(ARFLAGS))
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
	@$(ECHO) "| archiver          flags : $(CLR_UNDERLINE)$(ARFLAGS)$(CLR_WHITE)"
 endif
	@$(ECHO) "\\ -------------------------"

debug_all: pre
debug: multi

sanitize_all: pre
sanitize: multi

assembly_all: pre
assembly: multi

clean:
	@$(DEL) $(OBJS)
	@$(DEL) $(OBJS:.o=.s)
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
