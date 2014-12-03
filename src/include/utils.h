/**
 * @file utils.h
 * @brief utility header.
 * @author mopp
 * @version 0.1
 * @date 2014-09-27
 */


#ifndef _UTILS_H_
#define _UTILS_H_



#include <stddef.h>


extern void *memchr(void const*, int, size_t);
extern int memcmp(void const*, const void *, size_t);
extern void *memcpy(void *restrict, void const*restrict, size_t);
extern void *memset(void *, int, size_t);
extern int strcmp(char const*, char const*);
extern char *strcpy(char *, char const*);
extern size_t strlen(char const*);
extern char *strchr(char const *, int);
extern char *strrchr(char const*, int);
extern char *strstr(char const *, char const *);
extern size_t trim_tail(char *);
extern int isdigit(int);

extern int printf(char const*, ...);
extern char *itoa(int, char *, int);
extern int puts(char const*);
extern int putchar(int);



#endif
