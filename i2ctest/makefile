DIRS = examples bin lib
GARBPATS = *.o *.a
GARB:= $(foreach DIR, $(DIRS),$(addprefix $(DIR)/,$(GARBPATS)))

all:
	cd examples && $(MAKE) all
	cd lib && $(MAKE) all

lib:	.PHONY

.PHONY:
	cd lib && $(MAKE) all

example: .PHONY1

.PHONY1:
	cd examples && $(MAKE) example
clean:
	-rm -f $(GARB)
