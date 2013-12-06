#ifndef COMMON_H
#define COMMON_H

typedef enum {A_ALLOC = 0, A_FREE = 1, A_READ = 2, A_WRITE = 3} net_malloc_action_t;

typedef struct net_malloc_arg {
  net_malloc_action_t action;
  unsigned long       size;
} net_malloc_arg_t;

#endif
