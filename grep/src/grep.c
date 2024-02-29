#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_usage(char *prog_name)
{
	printf("Usage: %s [-hi] pattern filename\r\n", prog_name);
	printf("-h show this help message\r\n");
	printf("-i case insensitive matching\r\n");
}

void to_lower(char *str)
{
	for (int i = 0; str[i]; i++)
	{
		str[i] = tolower(str[i]);
	}
}

void match_pattern(bool insensitive, char *pattern, FILE *file)
{
	char line[1024];

	while (fgets(line, sizeof(line), file))
	{
		if (insensitive)
		{
			to_lower(pattern);
			to_lower(line);
		}

		if (strstr(line, pattern))
		{
			printf("%s", line);
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *file;
	bool insensitive = false;
	char *pattern = NULL;
	char *filename = NULL;

	for (int i = 1; i != argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0)
		{
			show_usage(argv[0]);

			return 0;
		}
		else if (strcmp(argv[i], "-i") == 0)
		{
			insensitive = true;
		}
		else if (!pattern)
		{
			pattern = argv[i];
		}
		else if (!filename)
		{
			filename = argv[i];
		}
		else
		{
			show_usage(argv[0]);

			return 0;
		}
	}

	if (pattern == NULL || filename == NULL)
	{
		show_usage(argv[0]);

		return 0;
	}

	if (!(file = fopen(filename, "r")))
	{
		fprintf(stderr, "Error opening file");

		return 1;
	}

	match_pattern(insensitive, pattern, file);
	fclose(file);

	return 0;
}