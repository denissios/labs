#define _CRT_SECURE_NO_WARNINGS

#include "menu.h"
#include "ht.h"
#include "parent.h"
#include "child.h"

const char* PARENT_DB_PATH = "parent.db";
const char* CHILD_DB_PATH = "child.db";

FILE* Parent_db = NULL,
	* Child_db  = NULL;

int main(void)
{
	ht_item* parent_ht = NULL, 
		   * child_ht  = NULL;
	if (fopen_s(&Parent_db, PARENT_DB_PATH, "a+b") || !ht_load(Parent_db, &parent_ht, create_empty_parent, read_parent, get_key_parent) ||
		fopen_s( &Child_db,  CHILD_DB_PATH, "a+b") || !ht_load( Child_db,  &child_ht,  create_empty_child,  read_child,  get_key_child))
		goto cleanup;

	dialog(parent_ht, child_ht);
	if (Parent_db) fclose(Parent_db); Parent_db = NULL;
	if ( Child_db) fclose( Child_db);  Child_db = NULL;

	if (fopen_s(&Parent_db, PARENT_DB_PATH, "wb") ||
		fopen_s( &Child_db,  CHILD_DB_PATH, "wb"))
		goto cleanup;

	ht_save(Parent_db, parent_ht, save_parent);
	ht_save( Child_db,  child_ht,  save_child);

cleanup:
	ht_dealloc(parent_ht, dealloc_parent);
	ht_dealloc( child_ht,  dealloc_child);

	if (Parent_db) fclose(Parent_db);
	if ( Child_db) fclose( Child_db);

	return 0;
}