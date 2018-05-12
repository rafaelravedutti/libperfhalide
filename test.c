#include "perf.h"

int main(int argc, const char *argv[]) {
  unsigned int i;

  perf_descriptor_start(PERF_MARKER_TEST);

  for(i = 0; i < 1000; ++i);

  perf_descriptor_stop(PERF_MARKER_TEST);
}
