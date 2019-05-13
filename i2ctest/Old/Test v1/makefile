#define compilation language type
CXX = gcc 
CXXFLAGS = -g -std=c11
#includes
#INCLUDES:= -I
DIRS = build/test build/lib
#libraries that need to be linked
LIBS =
#objects to make
OBJ = main.o
#
SRC = main.c
#
TSRC = main.c
#
GARBPATS = *.o
GARB:= $(foreach DIR, $(DIRS),$(addprefix $(DIR)/,$(GARBPATS)))
#
all: --dirs test lib
	#$(CXX) $(CXXFLAGS) $(SRC) -o build/$(OBJ)  $(LIBS)
#making testfiles	
test: --dirs
	$(CXX) $(CXXFLAGS) $(SRC) -o build/test/$(OBJ) $(LIBS)
	#@echo $(CXX) $(CXXFLAGS) $(SRC) -o build/test/$(OBJ) $(LIBS)

lib:
	@echo done
--dirs:
	-mkdir -p $(DIRS)
	@echo "Making output directories"
# generatic rule
%.o: %.c 
	$(CXX) $(CXXFLAGS) $^ -o build/lib/$@ $(LIBS)	
clean:
	-rm -f $(GARB)
	
