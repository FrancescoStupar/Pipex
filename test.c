#include "pipex.h"

char	*path(char *cmd, char **env)
{
	int		execstat;
	int gianni = open("demodei.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	printf("%i", gianni);
	dup2(gianni, 1);
	char *occhio = ft_strjoin("which ", cmd);
	char **olho = ft_split(occhio, ' ');
	execstat = execve("which", "which cat", env);
	if (execstat == -1)
	{
		perror("dedneqknd");
		exit(1);
	}
	//char *result = get_next_line(gianni);
	return ("ciao");
}

int main(int argc, char **argv, char **env)
{
	printf("%s", path(argv[1], env));
}