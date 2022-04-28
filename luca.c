#include "pipex.h"

void luca()
{
	int g = open("1.txt", O_RDONLY);
	printf("%s", get_next_line(g));
}