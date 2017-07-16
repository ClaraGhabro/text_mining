BUILD_DIR=build
HTML_DIR=html
LATEX_DIR=latex

all:
	+make -C $(BUILD_DIR)

doc:
	+make -C $(BUILD_DIR) $@

distclean:
	$(RM) text_mining
	$(RM) $(DIRS) $(BUILD_DIR)
	$(RM) $(HTML_DIR) $(LATEX_DIR)

%:
	+make -C $(BUILD_DIR) $@

.PHONY: doc
