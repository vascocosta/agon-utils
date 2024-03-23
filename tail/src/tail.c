#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_usage(char *prog_name)
{
	printf("Usage: %s [-hn] filename\r\n", prog_name);
	printf("-h show this help message\r\n");
	printf("-n print the last n lines (default: 10)\r\n");
}

void show_lines(FILE *file, int lines)
{
	char **buf = malloc(sizeof(char *) * lines);

	for (int i = 0; i < lines; i++)
		buf[i] = malloc(sizeof(char) * 1024);

	int lc = 0;

	while (fgets(buf[lc % lines], 1024, file) != NULL)
	{
		lc++;
	}

	int start = lc > lines ? lc % lines : 0;
	int count = lc > lines ? lines : lc;

	for (int i = 0; i < count; i++)
	{
		printf("%s", buf[(start + i) % lines]);
	}

	for (int i = 0; i < lines; i++)
		free(buf[i]);

	free(buf);
}

int main(int argc, char *argv[])
{
	FILE *file = NULL;
	char *filename = NULL;
	int parsed_lines = 0;
	size_t lines = 10;

	for (int i = 1; i != argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0)
		{
			show_usage(argv[0]);
			return 0;
		}
		else if (strncmp(argv[i], "-n", 2) == 0)
		{
			parsed_lines = atoi(argv[++i]);

			if (parsed_lines <= 0)
			{
				fprintf(stderr, "The number of lines must be positive");
				return 1;
			}

			lines = parsed_lines;
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

	show_lines(file, lines);
	fclose(file);

	return 0;
}