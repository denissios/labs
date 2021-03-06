#ifndef __PARENT_H_INCLUDED__
#define __PARENT_H_INCLUDED__

#include <stdbool.h>
#include <stdio.h>

typedef struct parent
{
	int key;
	size_t len;
	long offset;
} parent;

struct FILE;

parent* create_parent(FILE* f, const int key, char* info);

void* create_empty_parent(void);

void print_parent(FILE* f, const void* ptr);
bool read_parent(FILE* in, void* ptr);
void save_parent(FILE* out, const void* ptr);

inline const int get_key_parent(const void* ptr) { return ((const parent*)ptr)->key; }

#endif /* !__PARENT_H_INCLUDED__ */