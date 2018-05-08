# C compiler
CC=gcc

all: libperfhalide.so

perfhalide.o: perf.c
	${CC} -c -fPIC $^ -o $@

libperfhalide.so: perfhalide.o
	${CC} -shared -fPIC $^ -lc -o $@

clean:
	rm libperfhalide.so *.o
