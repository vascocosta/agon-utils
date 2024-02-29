#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void show_usage(char *prog_name)
{
	printf("Usage: %s [-hn] string\r\n", prog_name);
	printf("-h show this help message\r\n");
	printf("-n supress trailing newline\r\n");
}

int main(int argc, char *argv[])
{
	bool newline = true;

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-h") == 0)
			{
				show_usage(argv[0]);

				return 0;
			}

			if (strcmp(argv[i], "-n") == 0)
			{
				newline = false;

				continue;
			}

			printf("%s", argv[i]);

			if (i < argc - 1)
			{
				printf(" ");
			}
		}
	}

	if (newline)
	{
		printf("\r\n");
	}

	return 0;
}