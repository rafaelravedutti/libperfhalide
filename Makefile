# C compiler
CC=gcc
# C compilation flags
CFLAGS=-DPERF_VERBOSE

all: libperfhalide.so

perfhalide.o: perf.c
	${CC} -c -fPIC $^ -o $@ ${CFLAGS}

libperfhalide.so: perfhalide.o
	${CC} -shared -fPIC $^ -lc -o $@

install:
	cp -p libperfhalide.so /usr/lib

test: test.c libperfhalide.so
	${CC} $^ -L. -lperfhalide -o $@

clean:
	rm -f libperfhalide.so *.o test
