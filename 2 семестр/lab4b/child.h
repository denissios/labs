#ifndef __CHILD_H_INCLUDED__
#define __CHILD_H_INCLUDED__

#include <stdbool.h>
#include <stdio.h>

typedef struct child
{
	int key;
	int pkey;
	size_t len;
	char* info;
} child;

child* create_child(const int key, const int pkey, char* info);

void* create_empty_child(void);
void dealloc_child(void* ptr);

void print_child(const void* ptr);
bool read_child(FILE* in, void* ptr);
void save_child(FILE* out, const void* ptr);

inline const int get_key_child(const void* ptr) { return ((const child*)ptr)->key; }

#endif /* !__CHILD_H_INCLUDED__ */