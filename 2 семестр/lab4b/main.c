#define HT_SIZE 2

#include "menu.h"
#include "ht.h"
#include "parent.h"
#include "child.h"

#include <io.h>
#include <stdlib.h>

const char* DB_PATH = "db.txt";

FILE* DB = NULL;

int main(void)
{
	printf("Enter the name of file: ");
	char* DB_PATH = get_str();
	
	ht_item* parent_ht = NULL, 
		   * child_ht  = NULL;

	if (_access(DB_PATH, 0) == -1)
	{
		fopen_s(&DB, DB_PATH, "wbx");
		
		ht_alloc(&parent_ht);
		ht_alloc(&child_ht);
		
		ht_save(DB, parent_ht, save_parent);
		ht_save(DB, child_ht, save_child);
		
		if (DB) fclose(DB);
	}

	if (fopen_s(&DB, DB_PATH, "r+b") ||
		!ht_load(DB, &parent_ht, create_empty_parent, read_parent, get_key_parent) ||
		!ht_load(DB,  &child_ht,  create_empty_child,  read_child,  get_key_child))
		goto cleanup;

	dialog(parent_ht, child_ht);

	fseek(DB, 0, SEEK_SET);
	ht_save(DB, parent_ht, save_parent);
	ht_save(DB, child_ht, save_child);

cleanup:
	ht_dealloc(parent_ht);
	ht_dealloc( child_ht);

	if(DB) fclose(DB);

	return 0;
}