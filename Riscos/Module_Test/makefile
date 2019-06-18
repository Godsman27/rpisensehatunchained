# Final targets:
@.test: run
        gcc -o Module_test test.o -LOSLib: -lOSLib32
        @echo done
@.run:
	gcc -c -IOSLib: -o  test.o code.c
@.module:
	gcc -c -zm -mlibscl -mmodule -o test.o code.c
@.clean:
	*remove o.test
	*remove Module_test
	*remove o
# User-editable dependencies:

# Static dependencies:


# Dynamic dependencies:
