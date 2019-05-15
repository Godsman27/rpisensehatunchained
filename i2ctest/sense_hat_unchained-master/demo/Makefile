CFLAGS=-c -Wall -O2
LIBS= -lsensehat -lpthread -lm

all: sensedemo

sensedemo: main.o
	$(CC) main.o $(LIBS) -o sensedemo

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm *.o sensedemo

