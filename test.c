#include "pipex.h"

char *getpath()
{
	int g = open("/Users/fstupar/pipex/libft/1.txt", O_RDONLY);
	return(get_next_line(g));
}


//questa è funzione ft_strjoin vecchia, non va bene per get_next_line, ma quella che c'è adesso in libft non va bene per sto file
char	*ft_strjoinz(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		k;

	if (s1 == NULL || s1 == NULL)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		new[i] = s1[i];
	k = -1;
	while (s2[++k] != '\0')
		new[i + k] = s2[k];
	new[i + k] = '\0';
	return (new);
}

void	path(char *cmd, char **env)
{
	int pid;
	int		execstat;
	pid = fork();
	if (pid < 0)
	{
		perror("In process, Fork Error ");
		exit(1);
	}
	else if (pid == 0)
	{
		int gianni = open("/Users/fstupar/pipex/libft/1.txt", O_CREAT | O_RDWR| O_TRUNC, 0777);
		dup2(gianni, 1);
		char *occhio = ft_strjoinz("which ", cmd);
		char **olho = ft_split(occhio, ' ');
		execstat = execve("/usr/bin/which", olho, env);
		if (execstat == -1)
		{
			perror("dedneqknd");
			exit(1);
		}
	}
}	

int main(int argc, char **argv, char **env)
{
	path(argv[1], env);
	char *result = getpath();
	printf("%s", result);
	return 0;
}