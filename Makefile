include configs/base.mk
include configs/os.mk
include configs/colors.mk

.PHONY: make_optional all multi STATUS_START
multi: make_optional STATUS_START
	@$(MAKE) -e $(MAKE_PARALLEL_FLAGS) all

all: $(NAME)

$(NAME): $(OBJS) $(ASMS)
 ifneq (,$(OBJS))
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
 endif
	@$(MAKE) STATUS_END

define compilation
$(CC) $(addprefix -D,$(DEFINES)) \
	$(CFLAGS) $(CFLAGS_OPTIONAL) $(IFLAGS) \
	-c $$1 -o $$2
$(ECHO) " | $$2: $(MSG_SUCCESS)"
endef

-include $(OBJS:.o=.d)
$(OBJS): %.o: %.c
	@$(call compilation,$<,$@)

$(ASMS): %.S: %.c
	@$(call compilation,$<,$@)

-include configs/rules/STATUS.mk

-include configs/rules/cleaners.mk
.PHONY: re pre clean_asms clean_deps clean fclean

-include configs/rules/optional.mk
.PHONY: debug debug_all sanitize sanitize_all assembly assembly_all debug_assembly debug_assembly_all pedantic pedantic_all
