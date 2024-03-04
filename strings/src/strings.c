#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void show_usage(char *prog_name)
{
	printf("Usage: %s [-h] filename\r\n", prog_name);
	printf("-h show this help message\r\n");
}

void show_strings(FILE *file)
{
	int ch;
	const size_t max_len = 1024;
	size_t cur_len = 0;
	char buf[1024];

	while (fread(&ch, 1, 1, file) > 0)
	{
		if (cur_len < max_len)
		{
			if (ch == 10 || ch == 13 || (ch > 31 && ch < 128))
			{
				buf[cur_len++] = ch;
			}
		}
		else
		{
			fwrite(buf, 1, cur_len, stdout);
			cur_len = 0;
		}
	}

	if (cur_len < max_len)
	{
		fwrite(buf, 1, cur_len, stdout);
	}
}

int main(int argc, char *argv[])
{
	FILE *file = NULL;
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

	show_strings(file);
	printf("\r\n");
	fclose(file);

	return 0;
}