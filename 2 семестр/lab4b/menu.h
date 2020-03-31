#ifndef __MENU_H_INCLUDED__
#define __MENU_H_INCLUDED__

#include "ht.h"

void add_parent(ht_item* parent_ht, ht_item* child_ht);
void add_child(ht_item* parent_ht, ht_item* child_ht);
void remove_parent(ht_item* parent_ht, ht_item* child_ht);
void print_content(ht_item* parent_ht, ht_item* child_ht);
void print_menu(void);
void dialog(ht_item* parent_ht, ht_item* child_ht);

bool child_existence_for_deleting_parent(const ht_item* child_ht, const int pkey);
bool parent_existence_for_add_parent(const ht_item* parent_ht, const int key);
bool child_existence_for_add_child(const ht_item* child_ht, const int key);

#endif /* !__MENU_H_INCLUDED__ */