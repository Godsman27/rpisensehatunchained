all: setPixel
led: setPixel.o
	gcc -o $@ $+
setPixel.o : setPixel.s
	as -c -mfpu=vfpv2  -o $@ $<
clean:
	rm -vf setPixel *.o
