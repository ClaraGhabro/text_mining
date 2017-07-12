BUILD_DIR=build

all:
	+make -C $(BUILD_DIR)

distclean:
	$(RM) text_mining
#$(RM) $(DIRS) $(BUILD_DIR)

%:
	+make -C $(BUILD_DIR) $@
