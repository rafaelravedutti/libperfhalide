#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>
#include <papi.h>
//---
#include "perf.h"

static long perf_event_open(
  struct perf_event_attr *hw_event, pid_t pid,
  int cpu, int group_fd, unsigned long flags
) {
  return syscall(
    __NR_perf_event_open, hw_event, pid, cpu, group_fd, flags
  );
}

int get_perf_descriptor(int marker) {
  struct perf_event_attr pe;
  int fd;

  if(perf_fds[marker] != -1) {
    return perf_fds[marker];
  }

  memset(&pe, 0, sizeof(struct perf_event_attr));
  pe.type = PERF_TYPE_HARDWARE;
  pe.size = sizeof(struct perf_event_attr);
  pe.config = PERF_COUNT_HW_INSTRUCTIONS;
  pe.disabled = 1;
  pe.exclude_kernel = 1;
  pe.exclude_hv = 1;

  fd = perf_event_open(&pe, 0, -1, -1, 0);
  perf_assert(fd != -1);
  perf_fds[marker] = fd;

  return fd;
}

int perf_descriptor_start(int marker) {
  float real_time, proc_time, mflops;
  long long flpops;
  int ret;

  if((ret = PAPI_flops(&real_time, &proc_time, &flpops, &mflops)) < PAPI_OK) {
    fprintf(stderr, "Failed to initialize PAPI_flops (%d)\n", ret);
  }
}

int perf_descriptor_stop(int marker) {
  float real_time, proc_time, mflops;
  long long flpops;
  int ret;

  if((ret = PAPI_flops(&real_time, &proc_time, &flpops, &mflops)) < PAPI_OK) {
    fprintf(stderr, "Failed to use PAPI_flops (%d)\n", ret);
  } else {
    PERF_PRINT("Real time: %f, Proc time: %f, Total flpops: %lld, MFLOPS: %f\n", real_time, proc_time, flpops, mflops);
  } 
}

/*
int perf_descriptor_start(int marker) {
  int fd, ret;

  fd = perf_fds[marker];

  if(fd == -1) {
    fd = get_perf_descriptor(marker);
  }

  ret = ioctl(fd, PERF_EVENT_IOC_RESET, 0);
  perf_assert(ret >= 0);

  ret = ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
  perf_assert(ret >= 0);

  PERF_PRINT("Measuring instruction count...\n");

  return ret;
}

int perf_descriptor_stop(int marker) {
  int fd, ret;
  long long count;

  fd = perf_fds[marker];

  ret = ioctl(fd, PERF_EVENT_IOC_DISABLE, 0);
  perf_assert(ret >= 0);

  read(fd, &count, sizeof(long long));
  PERF_PRINT("Used %lld instructions\n", count);

  perf_fds[marker] = -1;
  close(fd);
  return 0;
}
*/

