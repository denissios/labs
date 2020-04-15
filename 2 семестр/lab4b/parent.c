#include "parent.h"
#include "ht.h"

#include <stdlib.h>
#include <string.h>

parent* create_parent(FILE* f, const int key, char* info)
{

	parent* ptr = (parent*)malloc(sizeof(parent));
	if (!ptr)
		return NULL;

	ptr->key = key;
	ptr->len = info ? strlen(info) : 0;

	fseek(f, 0, SEEK_END);
	ptr->offset = info? ftell(f) : 0;

	if (info)
		fwrite(info, sizeof(char), ptr->len, f);
	
	free(info);

	return ptr;
}

void* create_empty_parent(void)
{
	return calloc(1, sizeof(parent));
}

void print_parent(FILE* f, const void* ptr) 
{
	fseek(f, HT_TCPC(parent, ptr)->offset, SEEK_SET);

	char* buf = (char*)calloc(HT_TCPC(parent, ptr)->len + 1, sizeof(char));
	if (!buf)
		return;

	fread((void*)buf, sizeof(char), HT_TCPC(parent, ptr)->len, f);

	printf("|%5d|%10s|\n", HT_TCPC(parent, ptr)->key, buf);
	free(buf);
}

bool read_parent(FILE* in, void* ptr)
{
	return !(!ptr || fread(ptr, sizeof(parent), 1, in) != 1 || HT_TCPC(parent, ptr)->offset == 0);
}

void save_parent(FILE* out, const void* ptr)
{
	static const parent p = { 0, 0, 0 };
	fwrite(ptr? ptr : &p, sizeof(parent), 1, out);
}