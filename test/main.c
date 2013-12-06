#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "../common.h"

#define __NR_sys_netmalloc 333

void *netmalloc(unsigned long size) {
  net_malloc_arg_t arg;
  void *ptr = NULL;

  arg.action = A_ALLOC;
  arg.size = size;

  syscall(__NR_sys_netmalloc, &arg);

  return ptr;
}

void netfree(void *ptr) {
  net_malloc_arg_t arg;

  arg.action = A_FREE;

  syscall(__NR_sys_netmalloc, &arg);
}

int main() {

  char hello[] = "HELLO\0";
  char *ptr = netmalloc(sizeof(char) * 1000);
  netfree(ptr);
  
}
