#include <stdio.h>
#include <string.h>

void show_usage(char *prog_name)
{
	printf("Usage: %s [-h] filename\r\n", prog_name);
	printf("-h show this help message\r\n");
}

unsigned count_words(char *str)
{
	int state = 0;
	unsigned wc = 0;

	while (*str)
	{
		if (*str == ' ' || *str == '\n' || *str == '\t')
		{
			state = 0;
		}
		else if (state == 0)
		{
			state = 1;
			wc++;
		}
		str++;
	}

	return wc;
}

void show_counts(FILE *file)
{
	char line[1024];
	int lines = 0;
	int words = 0;
	int chars = 0;

	while (fgets(line, sizeof(line), file))
	{
		lines += 1;
		chars += strlen(line);
		words += count_words(line);
	}

	printf("%d lines %d words %d chars\r\n", lines, words, chars);
}

int main(int argc, char *argv[])
{
	FILE *file;
	char *filename = NULL;

	for (int i = 1; i != argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0)
		{
			show_usage(argv[0]);

			return 0;
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

	if (filename == NULL)
	{
		show_usage(argv[0]);

		return 0;
	}

	if (!(file = fopen(filename, "r")))
	{
		fprintf(stderr, "Error opening file");

		return 1;
	}

	show_counts(file);
	fclose(file);

	return 0;
}