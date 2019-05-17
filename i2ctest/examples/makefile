#examples
MAINDIR = /home/pi/Documents/rpisense/C/i2ctest/
CXX = gcc 
CXXFLAGS = -g -std=c11
INCFLAGS = -I$(MAINDIR)include

DIRS = $(MAINDIR)bin

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
DEP := $(wildcard *.h)
LIBS = $(MAINDIR)bin/sensehat.a

#libraries that need to be linked

all: lib $(OBJ)
	@echo "main make done!"

#making testfiles	
example: $(OBJ)

lib:
	@cd $(MAINDIR)/lib && $(MAKE)

# generatic rule
%.o: %.c 
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(SRC) -o $(OBJ) $(LIBS)
clean:
	-rm -f *.o
	
