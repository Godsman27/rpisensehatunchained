# Final targets:
@.target: run
        link -o Modsensehat -m o.cmodule o.cmodulehdr c:o.stubs o.sensehat
        @echo done
@.run:
	@mkdir o
	cmhg cmhg.CModuleHdr o.cmodulehdr h.cmodulehdr
	cc -c -zM c.Cmodule c.sensehat
@.clean:
	*wipe o.* ~V ~C
	*remove Modsensehat
	*remove o
# User-editable dependencies:

# Static dependencies:


# Dynamic dependencies:
