all: LEDKnots
led: LEDKnots.o
	gcc -o $@ $+
LEDKnots.o : LEDKnots.s
	as -c -mfpu=vfpv2  -o $@ $<
clean:
	rm -vf LEDKnots *.o
