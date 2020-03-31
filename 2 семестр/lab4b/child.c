#include "child.h"
#include "ht.h"

#include <stdlib.h>
#include <string.h>

child* create_child(const int key, const int pkey, char* info)
{
	child* ptr = (child*)malloc(sizeof(child));
	if (!ptr)
		return NULL;

	ptr->key = key;
	ptr->pkey = pkey;
	ptr->len = info ? strlen(info) : 0;
	ptr->info = info;

	return ptr;
}

void* create_empty_child(void)
{
	child* ptr = (child*)malloc(sizeof(child));
	if (!ptr)
		return NULL;

	ptr->key = 0;
	ptr->pkey = 0;
	ptr->len = 0;
	ptr->info = NULL;

	return (void*)ptr;
}

void dealloc_child(void* ptr)
{
	free(HT_TPC(child, ptr)->info);
	free(ptr);
}

void print_child(const void* ptr)
{
	printf_s("|%5d|%5d|%10s|\n", HT_TCPC(child, ptr)->key, HT_TCPC(child, ptr)->pkey, HT_TCPC(child, ptr)->info);
}

bool read_child(FILE* in, void* ptr)
{
	if (!ptr ||
		fread(&HT_TPC(child, ptr)->key, sizeof(int), 1, in) != 1 ||
		fread(&HT_TPC(child, ptr)->pkey, sizeof(int), 1, in) != 1 ||
		fread(&HT_TPC(child, ptr)->len, sizeof(size_t), 1, in) != 1)
		return false;

	HT_TPC(child, ptr)->info = (char*)calloc(HT_TPC(child, ptr)->len + 1, sizeof(char));
	if (!HT_TPC(child, ptr)->info ||
		fread(HT_TPC(child, ptr)->info, sizeof(char), HT_TPC(child, ptr)->len, in) != HT_TPC(child, ptr)->len)
	{
		free(HT_TPC(child, ptr)->info);

		return false;
	}

	return true;
}

void save_child(FILE* out, const void* ptr)
{
	fwrite(&HT_TCPC(child, ptr)->key, sizeof(int), 1, out);
	fwrite(&HT_TCPC(child, ptr)->pkey, sizeof(int), 1, out);
	fwrite(&HT_TCPC(child, ptr)->len, sizeof(size_t), 1, out);
	fwrite(HT_TCPC(child, ptr)->info, sizeof(char), HT_TCPC(child, ptr)->len, out);
}