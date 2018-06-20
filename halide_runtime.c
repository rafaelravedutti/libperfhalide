#include <stdio.h>
#include <HalideRuntime.h>

int halide_profiler_set_current_func(struct halide_profiler_state *state, int tok, int t) {
    fprintf(stdout, "halide_profiler_set_current_func\n");

    volatile int *ptr = &(state->current_func);
    asm volatile ("":::);
    *ptr = tok + t;
    asm volatile ("":::);
    return 0;
}

int halide_profiler_incr_active_threads(struct halide_profiler_state *state) {
    fprintf(stdout, "halide_profiler_incr_active_threads\n");

    volatile int *ptr = &(state->active_threads);
    asm volatile ("":::);
    int ret = __sync_fetch_and_add(ptr, 1);
    asm volatile ("":::);
    return ret;
}

int halide_profiler_decr_active_threads(struct halide_profiler_state *state) {
    fprintf(stdout, "halide_profiler_decr_active_threads\n");

    volatile int *ptr = &(state->active_threads);
    asm volatile ("":::);
    int ret = __sync_fetch_and_sub(ptr, 1);
    asm volatile ("":::);
    return ret;
}
