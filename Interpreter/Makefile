CFLAGS ?= -Wall -Wextra -pedantic -g

all: staple
staple: darray.o dvalue.o parser.o runner.o staple.o stdops.o symenc.o vendor/linenoise.o
	$(CC) $(CCFLAGS) $^ -o staple

darray.o: darray.c darray.h dvalue.h
dvalue.o: dvalue.c dvalue.h
parser.o: parser.c parser.h darray.h dvalue.h
runner.o: runner.c runner.h darray.h dvalue.h stdops.h
staple.o: staple.c staple.h parser.h darray.h dvalue.h runner.h stdops.h vendor/linenoise.h
stdops.o: stdops.c stdops.h darray.h dvalue.h
symenc.o: symenc.c symenc.h
vendor/linenoise.o: vendor/linenoise.c vendor/linenoise.h

clean:
	rm -rvf *.o vendor/linenoise.o

.PHONY: clean
