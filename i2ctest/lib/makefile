MAINDIR = /home/pi/Documents/rpisense/C/i2ctest/
CXX = gcc 
CXXFLAGS = -c -std=c11
INCFLAGS = -I $(MAINDIR)include

DIRS = $(MAINDIR)bin

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
DEP := $(wildcard *.h)

#
all: --sensehat.a
	
--sensehat.a: lib
	ar rcs sensehat.a $(OBJ) 
	cp -u  $(DEP) $(MAINDIR)include/
	cp -u sensehat.a $(DIRS)

lib: --dirs $(OBJ)

--dirs:
	-mkdir -p $(DIRS)
	
# generatic rule
%.o: %.c 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

clean:
	-rm -f $(DIRS)/*.o *.o *.a 
	
