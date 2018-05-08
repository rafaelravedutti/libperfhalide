# C compiler
CC=gcc
# C compilation flags
CFLAGS=-DPERF_VERBOSE

all: libperfhalide.so

perfhalide.o: perf.c
	${CC} -c -fPIC $^ -o $@ ${CFLAGS}

libperfhalide.so: perfhalide.o
	${CC} -shared -fPIC $^ -lc -o $@

clean:
	rm -f libperfhalide.so *.o
