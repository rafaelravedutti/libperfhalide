# C compiler
CC=gcc
# C compilation flags
CFLAGS=-DPERF_VERBOSE

# Halide directories
HALIDE_DIR=/home/rafael/hdd/repositories/Halide
HALIDE_RUNTIME_DIR=${HALIDE_DIR}/src/runtime

# Halide flags
HALIDE_FLAGS=-I ${HALIDE_RUNTIME_DIR}

all: libperfhalide.so

perfhalide.o: perf.c
	${CC} -c -fPIC $^ -o $@ ${CFLAGS}

halide_runtime.o: halide_runtime.c
	${CC} -c -fPIC $^ -o $@ ${CFLAGS} ${HALIDE_FLAGS}

libperfhalide.so: perfhalide.o halide_runtime.o
	${CC} -shared -fPIC $^ -lc -o $@

install:
	cp -p libperfhalide.so /usr/lib

test: test.c libperfhalide.so
	${CC} $^ -L. -lperfhalide -lpapi -o $@

clean:
	rm -f libperfhalide.so *.o test
