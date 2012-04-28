all: Interpreter Documentation

Interpreter:
	cd Interpreter && $(MAKE)

Documentation: Documentation/Stdlib.mkd
Documentation/Stdlib.mkd: Interpreter/stdops.c
	./Support/mkstdlibdoc.sh

check:
	find Tests/ -name \*.St -print -exec Interpreter/staple {} \;

.PHONY: Interpreter Documentation
