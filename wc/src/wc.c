#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void show_usage(char *prog_name)
{
	printf("Usage: %s [-chlw] filename\r\n", prog_name);
	printf("-c print the characters count\r\n");
	printf("-h show this help message\r\n");
	printf("-l print the lines count\r\n");
	printf("-w print the words count\r\n");
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

void show_counts(FILE *file, bool lines, bool words, bool chars)
{
	char line[1024];
	int lc = 0;
	int wc = 0;
	int cc = 0;

	while (fgets(line, sizeof(line), file))
	{
		lc += 1;
		cc += strlen(line);
		wc += count_words(line);
	}

	if (!(lines || words || chars))
	{
		printf("%d %d %d", lc, wc, cc);
	}
	else
	{
		if (lines)
		{
			printf("%d ", lc);
		}

		if (words)
		{
			printf("%d ", wc);
		}

		if (chars)
		{
			printf("%d", cc);
		}
	}

	printf("\r\n");
}

int main(int argc, char *argv[])
{
	FILE *file = NULL;
	char *filename = NULL;
	bool lines = false;
	bool words = false;
	bool chars = false;

	for (int i = 1; i != argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0)
		{
			show_usage(argv[0]);

			return 0;
		}
		else if (strcmp(argv[i], "-l") == 0)
		{
			lines = true;
		}
		else if (strcmp(argv[i], "-w") == 0)
		{
			words = true;
		}
		else if (strcmp(argv[i], "-c") == 0)
		{
			chars = true;
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

	show_counts(file, lines, words, chars);
	fclose(file);

	return 0;
}