#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BUF_LEN 256

char* get_str(void);
bool substr_exists(const char* substr, const size_t length, const char* str);
void find_word(const char* str, const char** start, const char** end);
char* proceed(const char* str1, const char* str2);

int main(void)
{
	size_t count = 1;
	bool  flag = false;
	while (!flag)
	{
		printf("Enter%u: ", count++);
		char* str1 = get_str();
		printf("Enter%u: ", count++);
		char* str2 = get_str();

		char* result = NULL;
		if (!str1 || !str2)
			flag = true;
		else
			result = proceed(str1, str2);

		printf("Result: \"%s\"\n", result);
		printf("\n");

		free(result);
		free(str1);
		free(str2);
	}

	return 0;
}

char* get_str(void)
{
	char buf[BUF_LEN] = "";
	size_t str_len = 0;
	char* str = (char*)malloc(1);
	if (!str)
	{
		printf("Cannot allocate");
		return NULL;
	}

	*str = '\0';

	int n = 0;
	do {
		n = scanf_s("%255[^\n]", buf, BUF_LEN);
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

bool substr_exists(const char* substr, const size_t length, const char* str)
{
	char* start = NULL,
		* end = NULL;
	while (*str)
	{
		find_word(str, &start, &end);

		size_t len = end - start;
		if (len == length && !strncmp(substr, start, len))
			return true;

		str = end;
	}

	return false;
}

void find_word(const char* str, const char** start, const char** end)
{
	while (*str && isspace(*str)) ++str;
	*start = str;

	while (*str && !isspace(*str)) ++str;
	*end = str;
}

char* proceed(const char* str1, const char* str2)
{
	size_t str1_length = strlen(str1);
	if (!str1_length)
		str1_length = 1;

	size_t result_length = 0;
	char* result = (char*)calloc(str1_length, sizeof(char));
	if (!result)
	{
		exit(1);
	}

	const char* tmp = str1,
		* start = NULL,
		* end = NULL;
	while (*tmp)
	{
		find_word(tmp, &start, &end);

		size_t length = end - start;
		if (substr_exists(start, length, str2) && !substr_exists(start, length, result))
		{
			result_length += length + 1;

			strncat(result, start, length);
			strcat(result, " ");
		}

		tmp = end;
	}

	char* tmp_ptr = (char*)realloc(result, result_length ? result_length-- : 1);
	if (!tmp_ptr)
	{
		printf("Cannot reallocate");
		free(result);

		exit(1);
	}

	result = tmp_ptr;
	result[result_length] = '\0';

	return result;
}