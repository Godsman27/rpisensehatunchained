DIRS = examples bin lib
GARBPATS = *.o *.a
GARB:= $(foreach DIR, $(DIRS),$(addprefix $(DIR)/,$(GARBPATS)))

all:
	cd examples && $(MAKE)
	cd lib && $(MAKE)
clean:
	-rm -f $(GARB)