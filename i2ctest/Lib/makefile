#define compilation language type
CXX = gcc 
CXXFLAGS = -g -std=c11
#includes
#INCLUDES:= -I
DIRS = ../build/test ../build/lib


#libraries that need to be linked

#objects to make
OBJ = 
#
SRC = 
#
HEADER = sensehat.h
LIBSRC = sensehat.c
LIBDIR = ../build/lib
LIBOBJ = sensehat.o
GARBPATS = *.o
GARB:= $(foreach DIR, $(DIRS),$(addprefix $(DIR)/,$(GARBPATS)))

sensehat.a: lib
	ar rcs $(LIBDIR)/sensehat.a $(LIBDIR)/$(LIBOBJ) 
	cp -u  $(HEADER) ../include/$(HEADER)
lib:
	@echo done
	$(CXX) $(CXXFLAGS) -c $(LIBSRC) -o $(LIBDIR)/$(LIBOBJ)
	
# generatic rule
%.o: %.c 
	$(CXX) $(CXXFLAGS) -c $^ -o $(LIBDIR)/$@ $(LIBS)

clean:
	-rm -f $(GARB)
	
