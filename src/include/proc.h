/**
 * @file include/proc.h
 * @brief process header.
 * @author mopp
 * @version 0.1
 * @date 2014-07-15
 */

#ifndef _PROC_H_
#define _PROC_H_



#include <state_code.h>
#include <stdbool.h>
#include <stdint.h>
#include <paging.h>
#include <elist.h>
#include <interrupt.h>


struct thread {
    uintptr_t sp; /* Stack pointer. */
    uintptr_t ip; /* Instruction pointer. */
    Interrupt_frame* iframe;
};
typedef struct thread Thread;


struct frame_chain {
    Elist l;
    Frame* f;
};
typedef struct frame_chain Frame_chain;


struct segment {
    uintptr_t addr;
    size_t size;
};
typedef struct segment Segment;


enum User_segmentss_constants {
    DEFAULT_STACK_SIZE        = FRAME_SIZE,
    DEFAULT_STACK_TOP_ADDR    = 0x2000,
    DEFAULT_STACK_BOTTOM_ADDR = DEFAULT_STACK_TOP_ADDR + DEFAULT_STACK_SIZE,
    DEFAULT_TEXT_SIZE         = FRAME_SIZE,
    DEFAULT_TEXT_ADDR         = 0x1000,
};


struct user_segments {
    Segment text;
    Segment data;
    Segment stack;
};
typedef struct user_segments User_segments;


struct process {
    uint8_t priority;
    uint8_t state;
    uint16_t pid;
    uint32_t cpu_time;
    Elist used_pages;
    User_segments u_segs;
    Thread thread;
    struct process* parent;
    uintptr_t km_stack;
    Page_directory_table pdt;
    Page pdt_page;
};
typedef struct process Process;


Axel_state_code init_process(void);
void switch_context(Interrupt_frame*);
Process* running_proc(void);
Process* pdt_proc(void);

extern bool is_enable_process;



#endif
