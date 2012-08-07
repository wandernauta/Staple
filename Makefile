all: Interpreter Documentation

Interpreter:
	cd Interpreter && $(MAKE)

Documentation: Documentation/Standard?Library.mkd
Documentation/Standard?Library.mkd: Interpreter/stdops.c
	./Support/mkstdlibdoc.sh

check:
	find Tests -name \*.St -depth 1 -print -exec Interpreter/staple {} \;

check_ops:
	find Tests/Ops -name \*.St -print -exec Interpreter/staple {} \;

.PHONY: Interpreter Documentation
