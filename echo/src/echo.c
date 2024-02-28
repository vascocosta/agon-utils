#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i;
	bool new_line = true;

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-n") == 0)
			{
				new_line = false;
				continue;
			}

			printf("%s ", argv[i]);
		}
	}

	if (new_line)
	{
		printf("\r\n");
	}

	return 0;
}