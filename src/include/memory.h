/**
 * @file include/memory.c
 * @brief some memory functions.
 * @author mopp
 * @version 0.1
 * @date 2014-05-20
 */

#ifndef MEMORY_H
#define MEMORY_H


#include <stdint.h>
#include <stddef.h>
#include <list.h>
#include <multiboot.h>


enum memory_manager_constants {
    MAX_MEM_NODE_NUM = 4096, /* MAX_MEM_NODE_NUM(0x1000) must be a power of 2 for below modulo. */
    MEM_INFO_STATE_FREE = 0, /* this shows that we can use its memory. */
    MEM_INFO_STATE_ALLOC,    /* this shows that we cannot use its memory. */
};
#define MOD_MAX_MEM_NODE_NUM(n) (n & 0x07ffu)


/* memory infomation structure to managed. */
struct memory_info {
    uintptr_t base_addr; /* base address */
    uint32_t state;      /* managed area state */
    size_t size;         /* allocated size */
};
typedef struct memory_info Memory_info;


/* structure for storing memory infomation. */
struct memory_manager {
    /* this list store memory infomation using Memory_info structure. */
    List list;
};
typedef struct memory_manager Memory_manager;


/* リンカスクリプトで設定される数値を取得 */
extern uintptr_t get_kernel_start_addr(void);
extern uintptr_t get_kernel_end_addr(void);
extern uintptr_t get_kernel_size(void);

extern void init_memory(Multiboot_memory_map const*, size_t);
extern void* malloc(size_t);
extern void free(void*);


#endif
