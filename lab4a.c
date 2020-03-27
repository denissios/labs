#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ht_size 10
#define OPTS_NUM 4
#define BUFFER_LENGTH 128

typedef struct ht_item
{
	bool busy;
	int key;
	void* value;
} ht_item;

typedef struct parent
{
	int key;
	char* info;
} parent;

typedef struct child
{
	int key;
	int pkey;
	char* info;
} child;

typedef void (*opt_t)(ht_item*, ht_item*);
typedef void (*dealloc_t)(void*);

char* get_str(void);
int get_int(const char* msg);

size_t ht_get_hash(const int key);
size_t ht_get_next(const size_t idx);
bool ht_item_add(ht_item* ht, const int key, void* value);
void* ht_item_read(ht_item* ht, const int key);
bool ht_item_delete(ht_item* ht, const int key, dealloc_t dealloc);
void ht_dealloc(ht_item* ht, dealloc_t dealloc);

parent* create_parent(const int key, char* info);
void print_parent(const parent* parent);
void print_parents(const ht_item* ht);

child* create_child(const int key, const int pkey, char* info);
void print_child(const child* child);
void print_childs(const ht_item* ht);

void add_parent(ht_item* parent_ht, ht_item* child_ht);
void add_child(ht_item* parent_ht, ht_item* child_ht);
void remove_parent(ht_item* parent_ht, ht_item* child_ht);
void print_content(ht_item* parent_ht, ht_item* child_ht);
void print_menu(const char** opts_msg);
void dialog(ht_item* parent_ht, ht_item* child_ht, opt_t* opts, const char** opts_msg);

bool child_existence_for_deleting_parent(const ht_item* child_ht, const int pkey);
bool parent_existence_for_add_parent(const ht_item* parent_ht, const int key);
bool child_existence_for_add_child(const ht_item* child_ht, const int key);

void dealloc_parent(void* p);
void dealloc_child(void* c);

int main(void)
{
	ht_item* parent_ht = (ht_item*)calloc(ht_size, sizeof(ht_item));
	ht_item* child_ht = (ht_item*)calloc(ht_size, sizeof(ht_item));

	opt_t opts[OPTS_NUM] =
	{
		&add_parent,
		&add_child,
		&remove_parent,
		&print_content
	};

	const char* opts_msg[OPTS_NUM] =
	{
		{ "Add parent" },
		{ "Add child" },
		{ "Remove parent" },
		{ "Print content" }
	};

	dialog(parent_ht, child_ht, opts, opts_msg);

	ht_dealloc(child_ht, dealloc_child);
	ht_dealloc(parent_ht, dealloc_parent);

	return 0;
}

char* get_str(void)
{
	char buf[BUFFER_LENGTH] = "";
	size_t str_len = 0;
	char* str = (char*)malloc(sizeof(char));
	if (!str)
	{
		printf("Cannot allocate");
		return NULL;
	}

	*str = '\0';

	int n = 0;
	do {
		n = scanf_s("%127[^\n]", buf, BUFFER_LENGTH);
		if (n == 1)
		{
			str_len += strlen(buf);
			char* tmp = (char*)realloc(str, str_len + 1);
			if (!tmp)
			{
				printf("Cannot reallocate");
				free(str);
				return NULL;
			}
			str = tmp;
			strcat(str, buf);
		}
		else if (!n)
			scanf_s("%*c");
		else
		{
			free(str);
			return NULL;
		}
	} while (n);

	return str;
}

int get_int(const char* msg)
{
	int res = 0;
	int ret_val = 0;
	while (!ret_val)
	{
		ret_val = scanf_s("%d", &res);
		if (!ret_val)
		{
			printf("[ERROR] Waiting for integer\n");
			scanf_s("%*[^\n]");
			printf("%s: ", msg);
		}
	}

	scanf_s("%*c");

	return res;
}

size_t ht_get_hash(const int key)
{
	return key % ht_size;
}

size_t ht_get_next(const size_t idx)
{
	return (idx + 1) % ht_size;
}

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

bool ht_item_delete(ht_item* ht, const int key, dealloc_t dealloc)
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

void ht_dealloc(ht_item* ht, dealloc_t dealloc)
{
	if (!ht)
		return;

	for (size_t i = 0; i < ht_size; ++i)
		if (ht[i].value)
			dealloc(ht[i].value);

	free(ht);
}

parent* create_parent(const int key, char* info)
{
	parent* p = (parent*)malloc(sizeof(parent));
	if (!p)
		return NULL;

	p->key = key;
	p->info = info;

	return p;
}

void print_parent(const parent* parent)
{
	printf("|%5d|%10s|\n", parent->key, parent->info);
}

void print_parents(const ht_item* ht)
{
	printf("|=====|==========|\n");
	printf("| KEY |   INFO   |\n");
	printf("|=====|==========|\n");
	for (size_t i = 0; i < ht_size; ++i)
		if (ht[i].value)
			print_parent((const parent*)ht[i].value);

	printf("|=====|==========|\n");
}

child* create_child(const int key, const int pkey, char* info)
{
	child* c = (child*)malloc(sizeof(child));
	if (!c)
		return NULL;

	c->key = key;
	c->pkey = pkey;
	c->info = info;

	return c;
}

void print_child(const child* child)
{
	printf("|%5d|%5d|%10s|\n", child->key, child->pkey, child->info);
}

void print_childs(const ht_item* ht)
{
	printf("|=====|=====|==========|\n");
	printf("| KEY | PKEY|   INFO   |\n");
	printf("|=====|=====|==========|\n");
	for (size_t i = 0; i < ht_size; ++i)
		if (ht[i].value)
			print_child((const child*)ht[i].value);

	printf("|=====|=====|==========|\n");
}

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

	parent* p = create_parent(key, info);

	if (!ht_item_add(parent_ht, p->key, (void*)p))
	{
		free(p);

		printf("[ERROR] Cannot add parent\n");
	}
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

	printf("PKey: ");
	int pkey = get_int("PKey");

	if (!ht_item_read(parent_ht, pkey))
	{
		printf("[ERROR] Parent key does not exists\n");

		return;
	}

	printf("Info: ");
	char* info = get_str();

	child* c = create_child(key, pkey, info);
	if (!ht_item_add(child_ht, c->key, (void*)c))
	{
		free(c);

		printf("[ERROR] Cannot add child\n");
	}
}

void remove_parent(ht_item* parent_ht, ht_item* child_ht)
{
	printf("Key: ");
	int key = get_int("Key");

	if (child_existence_for_deleting_parent(child_ht, key))
	{
		printf("[ERROR] Cannot delete parent(child exists)\n");

		return;
	}

	if (!ht_item_delete(parent_ht, key, dealloc_parent))
		printf("[ERROR] Cannot delete parent(he does not exists)\n");
}

void print_content(ht_item* parent_ht, ht_item* child_ht)
{
	printf("\nPARENTS TABLE\n");
	print_parents(parent_ht);

	printf("\nCHILDREN TABLE\n");
	print_childs(child_ht);

	printf("\n");
}

void print_menu(const char** opts_msg)
{
	printf("0. Exit\n");
	for (size_t i = 0; i < OPTS_NUM; ++i)
		printf("%zd. %s\n", i + 1, opts_msg[i]);

	printf("\n");
}

void dialog(ht_item* parent_ht, ht_item* child_ht, opt_t* opts, const char** opts_msg)
{
	while (1)
	{
		print_menu(opts_msg);

		printf("Your choice: ");
		int opt = get_int("Option");

		if (!opt)
			break;
		else if (opt < 0 || opt > OPTS_NUM)
			printf("[WARNING] Wrong option\n");
		else
			opts[opt - 1](parent_ht, child_ht);
	}
}

bool child_existence_for_deleting_parent(const ht_item* child_ht, const int pkey)
{
	for (size_t i = 0; i < ht_size; ++i)
		if (child_ht[i].value && ((child*)child_ht[i].value)->pkey == pkey)
			return true;

	return false;
}

bool parent_existence_for_add_parent(const ht_item* parent_ht, const int key)
{
	for (size_t i = 0; i < ht_size; ++i)
		if (parent_ht[i].value && ((parent*)parent_ht[i].value)->key == key)
			return true;

	return false;
}

bool child_existence_for_add_child(const ht_item* child_ht, const int key)
{
	for (size_t i = 0; i < ht_size; ++i)
		if (child_ht[i].value && ((parent*)child_ht[i].value)->key == key)
			return true;

	return false;
}

void dealloc_parent(void* p)
{
	free(((parent*)p)->info);
	free(p);
}

void dealloc_child(void* c)
{
	free(((child*)c)->info);
	free(c);
}
