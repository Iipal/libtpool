include configs/default_lib_config.mk

.PHONY: all multi STATUS_START
multi: STATUS_START
 ifneq (,$(filter $(MAKECMDGOALS),debug debug_all))
	@$(MAKE) $(MAKE_PARALLEL_FLAGS) CFLAGS="$(CFLAGS_DEBUG)" DEFINES="$(shell echo $(basename $(NAME)) | tr a-z A-Z)_DEBUG" all
 else
  ifneq (,$(filter $(MAKECMDGOALS),sanitize sanitize_all))
	@$(MAKE) $(MAKE_PARALLEL_FLAGS) CFLAGS="$(CFLAGS_SANITIZE)" DEFINES="$(shell echo $(basename $(NAME)) | tr a-z A-Z)_SANITIZE" all
  else
	@$(MAKE) $(MAKE_PARALLEL_FLAGS) all
  endif
 endif

STATUS_START:
	@$(ECHO) " | -------"
	@$(ECHO) " | making: $(CLR_UNDERLINE)$(NAME)$(CLR_WHITE) ..."
	@$(ECHO) " | -------"

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	@$(MAKE) STATUS

-include $(DEPS)
$(OBJS): %.o: %.c
	@$(CC) $(addprefix -D,$(DEFINES)) -c $(CFLAGS) $(CFLAGS_DEFAULT) $(IFLAGS) $< -o $@
	@$(ECHO) " | $@: $(MSG_SUCCESS)"

STATUS:
	@$(ECHO) "/"
	@$(ECHO) "|"
	@$(ECHO) "| created: $(NAME) $(MSG_SUCCESS)"
 ifneq (,$(DEFINES))
	@$(ECHO) "| compiler custom defines: $(foreach dfns,$(DEFINES),$(CLR_INVERT)$(dfns)$(CLR_WHITE) )"
 endif
	@$(ECHO) "| compiler default flags: $(CFLAGS_DEFAULT)"
	@$(ECHO) "| compiler optional flags: $(CLR_UNDERLINE)$(CFLAGS)$(CLR_WHITE)"
	@$(ECHO) "| archiver flags: $(CLR_UNDERLINE)$(ARFLAGS)$(CLR_WHITE)"
	@$(ECHO) "|"
	@$(ECHO) "\\"

debug_all: pre
debug: multi

sanitize_all: pre
sanitize: multi

clean:
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

.PHONY: re fclean clean norme del pre sanitize sanitize_all debug debug_all STATUS
