#include "ht.h"

#include <stdio.h>
#include <stdlib.h>

bool ht_item_add(ht_item* ht, const int key, void* value)
{
	size_t hash = ht_get_hash(key);
	size_t i = hash;
	do
	{
		if (!ht[i].value)
		{
			ht[i].busy = true;
			ht[i].key = key;
			ht[i].value = value;

			return true;
		}
		else if (ht[i].key == key)
			return false;

		i = ht_get_next(i);
	} while (i != hash);

	return false;
}

void* ht_item_read(ht_item* ht, const int key)
{
	size_t hash = ht_get_hash(key);
	size_t i = hash;
	do
	{
		if (!ht[i].busy)
			return NULL;
		else if (ht[i].value && ht[i].key == key)
			return ht[i].value;

		i = ht_get_next(i);
	} while (i != hash);

	return NULL;
}

bool ht_item_delete(ht_item* ht, const int key, dealloc_func_t dealloc)
{
	size_t hash = ht_get_hash(key);
	size_t i = hash;
	do
	{
		if (!ht[i].busy)
			return false;
		else if (ht[i].key == key)
		{
			dealloc(ht[i].value);

			ht[i].value = NULL;

			return true;
		}

		i = ht_get_next(i);
	} while (i != hash);

	return false;
}

inline void ht_alloc(ht_item** ht)
{
	if (ht && !*ht)
		*ht = (ht_item*)calloc(HT_SIZE, sizeof(ht_item));
}

void ht_dealloc(ht_item* ht, dealloc_func_t dealloc)
{
	if (!ht)
		return;

	for (size_t i = 0; i < HT_SIZE; ++i)
		if (ht[i].value)
			dealloc(ht[i].value);

	free(ht);
}

void ht_print(const ht_item* ht, print_func_t print)
{
	for (size_t i = 0; i < HT_SIZE; ++i)
		if (ht[i].value)
			print(ht[i].value);
}

bool ht_load(FILE* in, ht_item** ht, create_func_t create, read_func_t read, get_key_func_t get_key)
{
	if (!in)
		return false;

	ht_alloc(ht);
	if (!ht || !*ht)
		return false;

	fseek(in, 0, SEEK_SET);
	for (size_t i = 0; !feof(in) && i < HT_SIZE; ++i)
	{
		void* ptr = create();

		if (!ptr || !read(in, ptr))
		{
			free(ptr);

			break;
		}

		ht_item_add(*ht, get_key(ptr), ptr);
	}

	return true;
}

void ht_save(FILE* out, ht_item* ht, save_func_t save)
{
	if (!out)
		return;

	fseek(out, 0, SEEK_SET);
	for (size_t i = 0; i < HT_SIZE; ++i)
		if (ht[i].value)
			save(out, ht[i].value);
}