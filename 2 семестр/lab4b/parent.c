#include "parent.h"
#include "ht.h"

#include <stdlib.h>
#include <string.h>

parent* create_parent(const int key, char* info)
{
	parent* ptr = (parent*)malloc(sizeof(parent));
	if (!ptr)
		return NULL;

	ptr->key = key;
	ptr->len = info ? strlen(info) : 0;
	ptr->info = info;

	return ptr;
}

void* create_empty_parent(void)
{
	parent* ptr = (parent*)malloc(sizeof(parent));
	if (!ptr)
		return NULL;

	ptr->key = 0;
	ptr->len = 0;
	ptr->info = NULL;

	return (void*)ptr;
}

void dealloc_parent(void* ptr)
{
	free(HT_TPC(parent, ptr)->info);
	free(ptr);
}

void print_parent(const void* ptr)
{
	printf_s("|%5d|%10s|\n", HT_TCPC(parent, ptr)->key, HT_TCPC(parent, ptr)->info);
}

bool read_parent(FILE* in, void* ptr)
{
	if (!ptr ||
		fread(&HT_TPC(parent, ptr)->key, sizeof(int), 1, in) != 1 ||
		fread(&HT_TPC(parent, ptr)->len, sizeof(size_t), 1, in) != 1)
		return false;

	HT_TPC(parent, ptr)->info = (char*)calloc(HT_TPC(parent, ptr)->len + 1, sizeof(char));
	if (!HT_TPC(parent, ptr)->info ||
		fread(HT_TPC(parent, ptr)->info, sizeof(char), HT_TPC(parent, ptr)->len, in) != HT_TPC(parent, ptr)->len)
	{
		free(HT_TPC(parent, ptr)->info);

		return false;
	}

	return true;
}

void save_parent(FILE* out, const void* ptr)
{
	fwrite(&HT_TCPC(parent, ptr)->key, sizeof(int), 1, out);
	fwrite(&HT_TCPC(parent, ptr)->len, sizeof(size_t), 1, out);
	fwrite(HT_TCPC(parent, ptr)->info, sizeof(char), HT_TCPC(parent, ptr)->len, out);
}