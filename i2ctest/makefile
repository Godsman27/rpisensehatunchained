#define compilation language type
CXX = gcc 
CXXFLAGS = -g -std=c11
#includes
#INCLUDES:= -I include/
DIRS = build/test build/lib include

#libraries that need to be linked
LIBS = build/lib/sensehat.a

#objects to make
OBJ = main.o
#
SRC = main.c

#
GARBPATS = *.o *.a
GARB:= $(foreach DIR, $(DIRS),$(addprefix $(DIR)/,$(GARBPATS)))
#	


all: lib $(OBJ)
	@echo "main make done!"

#making testfiles	
test: --dirs lib
	$(CXX) $(CXXFLAGS) $(SRC) $(LIBS) -o build/test/$(OBJ) 
	#@echo $(CXX) $(CXXFLAGS) $(SRC) $(LIBS) -o build/test/$(OBJ) 

lib:	--dirs
	cd Lib && $(MAKE)
	@echo done

--dirs:
	-mkdir -p $(DIRS)
	@echo "Making output directories"

# generatic rule
%.o: %.c 
	$(CXX) $(CXXFLAGS) $^ -o build/$@ $(LIBS)	
clean:
	-rm -f $(GARB)
	
