all: main
led: main.o
	gcc -o $@ $+
main.o : main.s
	as -g -mfpu=vfpv2 -o $@ $<
clean:
	rm -vf main *.o
