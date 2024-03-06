#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_usage(char *prog_name)
{
	printf("Usage: %s [-hn min-len] filename\r\n", prog_name);
	printf("-h show this help message\r\n");
	printf("-n strings at least min-len long (default: 4)\r\n");
}

void show_str(int str_len, FILE *file)
{
	char ch;
	char buf[1024];
	int cur_len = 0;

	while (fread(&ch, 1, 1, file) > 0)
	{
		if ((int)ch > 31 && (int)ch < 128)
		{
			buf[cur_len++] = ch;
		}
		else if (cur_len >= str_len)
		{
			fwrite(buf, 1, cur_len, stdout);
			printf("\r\n");
			cur_len = 0;
		}
		else
		{
			cur_len = 0;
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *file = NULL;
	char *filename = NULL;
	int str_len = 4;

	for (int i = 1; i != argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0)
		{
			show_usage(argv[0]);

			return 0;
		}
		else if (strncmp(argv[i], "-n", 2) == 0)
		{
			str_len = atoi(argv[++i]);
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

	show_str(str_len, file);
	printf("\r\n");
	fclose(file);

	return 0;
}