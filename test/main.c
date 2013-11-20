#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define __NR_sys_netmalloc 333

void *netmalloc(unsigned long size) {
  void *ptr = NULL;

  syscall(__NR_sys_netmalloc, size, &ptr);

  return ptr;
}

int main() {

  char hello[] = "HELLO\0";
  char *ptr = netmalloc(sizeof(char) * 1000);
  
}
