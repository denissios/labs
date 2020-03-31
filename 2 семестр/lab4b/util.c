#include "util.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 128

char* get_str(void)
{
	char* str = (char*)malloc(sizeof(char));
	if (!str)
		return NULL;

	*str = '\0';

	char buf[BUFFER_LENGTH] = "";
	size_t str_len = 0;
	int n = 0;
	do {
		n = scanf_s("%127[^\n]", buf, BUFFER_LENGTH);
		if (n == 1)
		{
			str_len += strlen(buf);
			char* tmp_ptr = (char*)realloc(str, str_len + 1);
			if (!tmp_ptr)
			{
				free(str);

				return NULL;
			}

			str = tmp_ptr;
			strcat(str, buf);
			//strcat_s(str, sizeof(str), buf);
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
			printf_s("[ERROR] Waiting for integer\n");
			scanf_s("%*[^\n]");
			printf_s("%s: ", msg);
		}
	}

	scanf_s("%*c");

	return res;
}