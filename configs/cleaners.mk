.PHONY: clean_asms clean_deps clean fclean
clean_asms:
	@$(DEL) $(OBJS:%.o=%.S)
clean_deps:
	@$(DEL) $(OBJS:%.o=%.d)
clean: clean_deps clean_asms
	@$(DEL) $(OBJS)
fclean: clean
 ifneq (,$(wildcard $(NAME)))
	@$(DEL) $(NAME)
	@$(ECHO) " | $(CLR_INVERT)deleted$(CLR_WHITE): $(NPWD)"
 endif

.PHONY: re pre
pre: clean multi
re: fclean multi
