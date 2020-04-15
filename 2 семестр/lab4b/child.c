#include "child.h"
#include "ht.h"

#include <stdlib.h>
#include <string.h>

child* create_child(FILE* f, const int key, const int pkey, char* info)
{
	child* ptr = (child*)malloc(sizeof(child));
	if (!ptr)
		return NULL;

	ptr->key = key;
	ptr->pkey = pkey;
	ptr->len = info ? strlen(info) : 0;

	fseek(f, 0, SEEK_END);
	ptr->offset = info? ftell(f) : 0;
	if (info)
		fwrite(info, sizeof(char), strlen(info), f);
	free(info);

	return ptr;
}

void* create_empty_child(void)
{
	return calloc(1, sizeof(child));
}

void print_child(FILE* f, const void* ptr)
{
	fseek(f, HT_TCPC(child, ptr)->offset, SEEK_SET);

	void* buf = (char*)calloc(HT_TCPC(child, ptr)->len + 1, sizeof(char));
	if (!buf)
		return;

	fread(buf, sizeof(char), HT_TCPC(child, ptr)->len, f);

	printf("|%5d|%6d|%10s|\n", HT_TCPC(child, ptr)->key, HT_TCPC(child, ptr)->pkey, buf);
	
	free(buf);
}

bool read_child(FILE* in, void* ptr)
{
	return !(!ptr || fread(ptr, sizeof(child), 1, in) != 1 || ((child*)ptr)->offset == 0);
}

void save_child(FILE* out, const void* ptr)
{
	static const child c = { 0, 0, 0, 0 };
	fwrite(ptr ? ptr : &c, sizeof(child), 1, out);
}