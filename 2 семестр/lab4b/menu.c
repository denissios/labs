#include "menu.h"
#include "parent.h"
#include "child.h"
#include "util.h"

#include <stdlib.h>

#define OPTS_NUM 4

typedef void (*opt_t)(ht_item*, ht_item*);

const opt_t OPTS[OPTS_NUM] =
{
	&add_parent,
	&add_child,
	&remove_parent,
	&print_content
};

const char* OPTS_MSGS[OPTS_NUM] =
{
	{ "Add parent" },
	{ "Add child" },
	{ "Remove parent" },
	{ "Print content" }
};

extern FILE* Parent_db;
extern FILE* Child_db;

void add_parent(ht_item* parent_ht, ht_item* child_ht)
{
	(child_ht);

	printf("Key: ");
	int key = get_int("Key");

	if (parent_existence_for_add_parent(parent_ht, key))
	{
		printf("[ERROR] Cannot add parent (parent with this key has already exists)\n");

		return;
	}

	printf("Info: ");
	char* info = get_str();

	parent* ptr = create_parent(key, info);

	if (!ht_item_add(parent_ht, ptr->key, (void*)ptr))
	{
		free(ptr);

		printf("[ERROR] Cannot add parent\n");
	}
	else
		save_parent(Parent_db, ptr);
}

void add_child(ht_item* parent_ht, ht_item* child_ht)
{
	printf("Key: ");
	int key = get_int("Key");

	if (child_existence_for_add_child(child_ht, key))
	{
		printf("[ERROR] Cannot add child (child with this key has already exists)\n");

		return;
	}

	printf_s("PKey: ");
	int pkey = get_int("PKey");

	if (!ht_item_read(parent_ht, pkey))
	{
		printf_s("[ERROR] Parent key does not exists\n");

		return;
	}

	printf_s("Info: ");
	char* info = get_str();

	child* ptr = create_child(key, pkey, info);
	if (!ht_item_add(child_ht, ptr->key, (void*)ptr))
	{
		free(ptr);

		printf("[ERROR] Cannot add child\n");
	}
	else
		save_child(Child_db, ptr);
}

void remove_parent(ht_item* parent_ht, ht_item* child_ht)
{
	printf_s("Key: ");
	int key = get_int("Key");

	if (child_existence_for_deleting_parent(child_ht, key))
	{
		printf_s("[ERROR] Cannot delete parent(child exists)\n");

		return;
	}

	if (!ht_item_delete(parent_ht, key, dealloc_parent))
		printf_s("[ERROR] Cannot delete parent(he does not exists)\n");
}

void print_content(ht_item* parent_ht, ht_item* child_ht)
{
	printf_s("\nPARENTS TABLE\n");
	ht_print(parent_ht, print_parent);

	printf_s("\nCHILDREN TABLE\n");
	ht_print(child_ht, print_child);

	printf_s("\n");
}

void print_menu(void)
{
	printf_s("0. Exit\n");
	for (size_t i = 0; i < OPTS_NUM; ++i)
		printf_s("%zd. %s\n", i + 1, OPTS_MSGS[i]);

	printf_s("\n");
}

void dialog(ht_item* parent_ht, ht_item* child_ht)
{
	while (1)
	{
		print_menu();

		printf_s("Your choice: ");
		int opt = get_int("Option");

		if (!opt)
			break;
		else if (opt < 0 || opt > OPTS_NUM)
			printf_s("[WARNING] Wrong option\n");
		else
			OPTS[opt - 1](parent_ht, child_ht);
	}
}

bool child_existence_for_deleting_parent(const ht_item* child_ht, const int pkey)
{
	for (size_t i = 0; i < HT_SIZE; ++i)
		if (child_ht[i].value && ((child*)child_ht[i].value)->pkey == pkey)
			return true;

	return false;
}

bool parent_existence_for_add_parent(const ht_item* parent_ht, const int key)
{
	for (size_t i = 0; i < HT_SIZE; ++i)
		if (parent_ht[i].value && ((parent*)parent_ht[i].value)->key == key)
			return true;

	return false;
}

bool child_existence_for_add_child(const ht_item* child_ht, const int key)
{
	for (size_t i = 0; i < HT_SIZE; ++i)
		if (child_ht[i].value && ((parent*)child_ht[i].value)->key == key)
			return true;

	return false;
}