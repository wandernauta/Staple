all: Interpreter Documentation

Interpreter:
	cd Interpreter && $(MAKE)

Documentation: Documentation/Stdlib.mkd
Documentation/Stdlib.mkd: Interpreter/stdops.c
	./Support/mkstdlibdoc.sh

.PHONY: Interpreter Documentation
