include configs/base.mk
include configs/archiver.mk
include configs/compiler.mk
include configs/os.mk
include configs/colors.mk

.PHONY: make_optional all multi STATUS_START
multi: make_optional
	@$(MAKE) -e STATUS_START
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

-include configs/STATUS.mk
-include configs/optional_rules.mk
-include configs/cleaners.mk
