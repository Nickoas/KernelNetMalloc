#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include "common.h"

//Module definition
#define AUTHOR      "Nicolas KLARMAN and Claude RAMSEYER"
#define DESCRIPTION "NetMalloc for EPITECH"
#define LICENSE     "GPL"
#define NAME        "NetMalloc"

MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);
MODULE_LICENSE(LICENSE);


//Module parameters

static char *server = "127.0.0.1:12345";

module_param(server, charp, 0);
MODULE_PARM_DESC(server, "server argument. IP:PORT");

//Variables

char *ip;
char *port;

//Address
#if defined __X86_64__
#define __POINTER_TYPE 	uint64_t
#define BEGIN_ADDR 	((addr_t) 0xffffffff81000000)
#define END_ADDR 	((addr_t) 0xffffffffa2000000)
#define SPK 		"%lX"
#elif defined __i386__
#define __POINTER_TYPE 	uint32_t
#define BEGIN_ADDR	((addr_t) 0xc0000000)
#define END_ADDR	((addr_t) 0xd0000000)
#define SPK 		"%X"
#else
#error "Incorrect architecture"
#endif

typedef __POINTER_TYPE * addr_t;

#define __FIRST_SYSCALL_ADDR 	sys_close
#define __FIRST_SYSCALL_NUM 	__NR_close
#define INSERT_INDEX 333

static addr_t sys_saved = NULL;


void doAlloc(net_malloc_arg_t arg)
{
  printk(KERN_EMERG "Do Allocation\n");
}

void doFree(net_malloc_arg_t arg)
{
  printk(KERN_EMERG "Do Free\n");
}

/**
 *
 *
 */
asmlinkage int sys_netmalloc(net_malloc_arg_t *arg)
{
  switch(arg->action) {
  case A_ALLOC:
    doAlloc(arg);
    break;

  case A_FREE:
    doFree(arg);
    break;
  }
  return 0;
}

/**
 *
 *
 */
addr_t * find_systable(void)
{
	addr_t * table;
	addr_t i = BEGIN_ADDR;

	while (i < END_ADDR) {
		table = (addr_t *) i;
		if (table[__FIRST_SYSCALL_NUM] == (addr_t) __FIRST_SYSCALL_ADDR) {
			printk(KERN_INFO "Syscall table found at " SPK "\n", (__POINTER_TYPE) table);
			return table;
		}
		i++;
	}

	return NULL;
}

/**
 *
 *
 */
int my_module_init(void)
{
	addr_t * table;
	const char delimiter[] = ":";

	printk(KERN_INFO "Load My Module ...\n");

	table = find_systable();

	if (table == NULL) {
		return -1;
	}

	//Unlock write memory
	write_cr0(read_cr0() & (~ 0x10000));

	//Change syscall
	sys_saved = table[INSERT_INDEX];
	table[INSERT_INDEX] = (addr_t) sys_netmalloc;

	//Lock write memory
	write_cr0(read_cr0() | 0x10000);

	printk(KERN_INFO "... done!\n");


	printk(KERN_INFO "Check good parameter : %s\n", server);

	ip = strsep(&server, delimiter);
	port = strsep(&server, delimiter);

	//TODO others checks
	if (ip == NULL || port == NULL) {
	  printk(KERN_INFO "bad parameter\n");
	  return -1;
	}

	printk(KERN_INFO "ip='%s',port='%s'\n", ip, port);

	return 0;
}

/**
 *
 *
 */
void my_module_exit(void)
{
	addr_t * table;

	printk(KERN_INFO "Unload My Module ...\n");

	table = find_systable();

	if (table == NULL || sys_saved != NULL) {
		return;
	}

	//Unlock write memory
	write_cr0(read_cr0() & (~ 0x10000));

	//Replace syscall
	table[INSERT_INDEX] = sys_saved;

	//Lock write memory
	write_cr0(read_cr0() | 0x10000);

	printk(KERN_INFO "... done!\n");
}

//Module register
module_init(my_module_init);
module_exit(my_module_exit);
