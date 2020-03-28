#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define BUF_LEN 256

typedef struct node_t {
	char c;
	struct node_t* next;
} node_t;

void get_str(node_t* list);
void erase(node_t* head);
void DeallocateList(node_t* head);
node_t* AddNextNode(node_t* cur, const char c);
node_t* InsertNode(node_t* cur, const char c);
void RemoveNode(node_t* prev, node_t* cur);
void PrintList(const node_t* head);
node_t* add_num(node_t* cur, int num);

int main()
{
	while (1)
	{
		printf("Enter: ");
		node_t head = { '\0', NULL };
		get_str(&head);

		if (!head.next)
			break;

		erase(&head);

		printf("Result: ");
		PrintList(&head);
		printf("\n");

		DeallocateList(&head);
	}

	return 0;
}

void get_str(node_t* head)
{
	char buf[BUF_LEN] = "";

	node_t* cur = NULL;
	int n = 0;
	do
	{
		n = scanf_s("%255[^\n]", buf, BUF_LEN);
		if (n == 1)
		{
			size_t len = strlen(buf);
			for (size_t i = 0; i < len; ++i)
				cur = AddNextNode(!head->next ? head : cur, buf[i]);
		}
		else if (!n)
			scanf_s("%*c");
		else
		{
			DeallocateList(head);

			return;
		}
	} while (n > 0);

	if (!head->next)
		AddNextNode(head, '\0');
}

void erase(node_t* head)
{
	node_t* prev = head;
	node_t* ptr = prev->next;
	char c = '\0';

	while (ptr) // Searching for the first non-space character, also deleting last
		if (isspace(ptr->c))
		{
			RemoveNode(prev, ptr);

			ptr = prev->next;
		}
		else
		{
			c = ptr->c;

			break;
		}

	if (!c)
		return; // no symbols except space characters

	int del_num = 0;
	bool was_word = false;
	node_t* gp = prev;
	while (ptr)
	{
		if (ptr->c == c)
		{
			RemoveNode(prev, ptr);
			del_num++;
			was_word = true;

			ptr = prev->next;

			continue;
		}
		else if (isspace(ptr->c))
		{
			if (was_word)
			{
				was_word = false;
				gp = add_num(prev, del_num);
				del_num = 0;
				prev = gp->next;
				prev->c = ' ';
				ptr = prev->next;
			}
			else
			{
				RemoveNode(prev, ptr);

				ptr = prev->next;
			}

			continue;
		}

		was_word = true;

		gp = prev;
		prev = ptr;
		ptr = ptr->next;
	}

	if (was_word)
		add_num(prev, del_num);
	else if (gp->c == ')')
		RemoveNode(gp, prev);
}

void DeallocateList(node_t* head)
{
	head = head->next;
	while (head)
	{
		node_t* tmp_ptr = head->next;

		free(head);

		head = tmp_ptr;
	}
}

node_t* AddNextNode(node_t* cur, const char c)
{
	cur->next = (node_t*)calloc(1, sizeof(node_t));
	if (!cur->next)
		printf("Cannot allocate memory for node\n");
	else
		cur->next->c = c;

	return cur->next;
}

node_t* InsertNode(node_t* cur, const char c)
{
	node_t* ptr = cur->next;
	cur->next = AddNextNode(cur, c);
	cur->next->next = ptr;

	return cur->next;
}

void RemoveNode(node_t* prev, node_t* cur)
{
	node_t* ptr = cur->next;

	free(prev->next);

	prev->next = ptr;
}

void PrintList(const node_t* head)
{
	const node_t* ptr = head->next;
	printf("\"");
	while (ptr && ptr->c)
	{
		printf("%c", ptr->c);

		ptr = ptr->next;
	}
	printf("\"\n");
}

node_t* add_num(node_t* cur, int num)
{
	node_t* ptr = InsertNode(cur, '(');

	if (!num)
		ptr = InsertNode(ptr, '0');
	else
	{
		node_t* end = InsertNode(ptr, '0' + num % 10);
		while (num /= 10)
		{
			InsertNode(ptr, '0' + num % 10);

			num /= 10;
		}

		ptr = end;
	}

	return InsertNode(ptr, ')');
}