#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void match_pattern(FILE *file, const char *pattern)
{
	char line[1024];

	while (fgets(line, sizeof(line), file))
	{
		if (strstr(line, pattern))
		{
			printf("%s", line);
		}
	}
}

void show_usage(char *prog_name)
{
	printf("Usage: %s <pattern> <filename>\r\n", prog_name);
}

int main(int argc, char *argv[])
{
	FILE *file;
	const char *filename;
	const char *pattern;

	if (argc != 3)
	{
		show_usage(argv[0]);

		return 0;
	}

	filename = argv[2];
	pattern = argv[1];

	if (!(file = fopen(filename, "r")))
	{
		fprintf(stderr, "Error opening file");

		return 1;
	}

	match_pattern(file, pattern);
	fclose(file);

	return 0;
}