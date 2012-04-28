CFLAGS ?= -Wall -Wextra -pedantic -g

all: staple tags
staple: darray.o dvalue.o parser.o runner.o staple.o stdops.o symenc.o vendor/linenoise.o
	$(CC) $(CCFLAGS) $^ -o staple -lm

darray.o: darray.c darray.h dvalue.h symenc.h
dvalue.o: dvalue.c dvalue.h symenc.h
parser.o: parser.c parser.h darray.h dvalue.h symenc.h
runner.o: runner.c runner.h darray.h dvalue.h symenc.h stdops.h
staple.o: staple.c staple.h darray.h dvalue.h symenc.h parser.h runner.h stdops.h vendor/linenoise.h
stdops.o: stdops.c stdops.h darray.h dvalue.h symenc.h
symenc.o: symenc.c symenc.h

vendor/linenoise.o: vendor/linenoise.c vendor/linenoise.h

clean:
	rm -rvf *.o vendor/linenoise.o tags

check:
	find . -name \*.c -or -name \*.h -exec cppcheck --enable=all -q {} \;

tags: $(wildcard *.c) $(wildcard *.h)
	@ctags *.c *.h

.PHONY: clean check
