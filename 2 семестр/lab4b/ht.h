#ifndef __HT_H_INCLUDED__
#define __HT_H_INCLUDED__

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#ifndef HT_SIZE
#define HT_SIZE 10
#endif /* !HT_SIZE */

#define HT_TYPE_PCAST(type, value) ((type*)(value))
#define HT_TYPE_CPCAST(type, value) ((const type*)(value))

#define HT_TPC(type, value) HT_TYPE_PCAST(type, value)
#define HT_TCPC(type, value) HT_TYPE_CPCAST(type, value)

typedef struct ht_item
{
	bool busy;
	int key;
	void* value;
} ht_item;

typedef void (*dealloc_func_t)(void*);
typedef void* (*create_func_t)(void);
typedef void (*print_func_t)(const void*);
typedef bool (*read_func_t)(FILE*, void*);
typedef void (*save_func_t)(FILE*, const void*);
typedef const int (*get_key_func_t)(const void*);

inline size_t ht_get_hash(const int key) { return key % HT_SIZE; }
inline size_t ht_get_next(const size_t idx) { return (idx + 1) % HT_SIZE; }
bool ht_item_add(ht_item* ht, const int key, void* value);
void* ht_item_read(ht_item* ht, const int key);
bool ht_item_delete(ht_item* ht, const int key, dealloc_func_t dealloc);

inline void ht_alloc(ht_item** ht);
void ht_dealloc(ht_item* ht, dealloc_func_t dealloc);

void ht_print(const ht_item* ht, print_func_t);
bool ht_load(FILE* in, ht_item** ht, create_func_t create, read_func_t read, get_key_func_t get_key);
void ht_save(FILE* out, ht_item* ht, save_func_t save);

#endif /* !__HT_H_INCLUDED__ */