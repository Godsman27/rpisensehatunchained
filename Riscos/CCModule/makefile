# Final targets:
@.target: run
        link -o Modsensehat -m o.cmodule o.cmodulehdr c:o.stubs o.test
        @echo done
@.run:
	cmhg cmhg.CModuleHdr o.cmodulehdr h.cmodulehdr
	cc -c -zM c.Cmodule c.sensehat
@.clean:
	*wipe ~V ~C o.*
	*remove Cmodule
# User-editable dependencies:

# Static dependencies:


# Dynamic dependencies:
