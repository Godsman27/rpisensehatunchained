# Final targets:
@.test: run
        link -o cmodule -m o.cmodule o.cmodulehdr c:o.stubs o.test
        @echo done
@.run:
	cmhg cmhg.CModuleHdr o.cmodulehdr h.cmodulehdr
	cc -c -zM c.Cmodule c.code
@.clean:
	*wipe ~V ~C o.*
	*remove Cmodule
# User-editable dependencies:

# Static dependencies:


# Dynamic dependencies:
