#define compilation language type
CXX = gcc 
CXXFLAGS = -g -std=c11
#includes
#INCLUDES:= -I

#libraries that need to be linked
LIBS = -lsense
#objects to make
OBJ = main.o
#
SRC = main.c
#
TSRC = main.c
#
all:
	-mkdir -p build
	$(CXX) $(CXXFLAGS) $(SRC) -o build/$(OBJ)  $(LIBS)
	make test
#	
test:
	-mkdir -p build/test
	$(CXX) $(CXXFLAGS) $(SRC) -o build/test/$(OBJ) $(LIBS)
	-echo $(CXX) $(CXXFLAGS) $(SRC) -o build/test/$(OBJ) $(LIBS) 
#
$(OBJ): %.o: %.c
	$(CXX) $(CXXFLAGS) $(inputs) -o $(outputs) $(LIBS)
clean:
	-rm -f build/$(OBJ)
	-rm -f build/test/$(OBJ)
#%.o: %.c
#	$(CXX) $(CXXFLAGS)
