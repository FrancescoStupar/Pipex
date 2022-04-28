/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstupar <fstupar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:32:29 by fstupar           #+#    #+#             */
/*   Updated: 2022/04/19 14:50:36 by fstupar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	puterror(char *str)
{
	perror(str);
	exit(-1);
}

// char	*path(char *cmd, char **env)
// {
// 	int		execstat;
// 	int gianni = open("demodei.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
// 	dup2(gianni, 1);
// 	char *occhio = ft_strjoin("which ", cmd);
// 	char **olho = ft_split(occhio, ' ');
// 	execstat = execve("which", olho, env);
// 	if (execstat == -1)
// 		puterror("dedneqknd");
// 	char *result = get_next_line(gianni);
// 	return ("/bin/cat");
}

void	process1(char **argv, char **env, int fd[2], int x)
{
	int		execstat;
	int		pid;
	char	**cmds;
	char 	*cmd;

	pid = fork();
	if (pid < 0)
		puterror("In process, Fork Error ");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(x, 0);
		cmds = ft_split(argv[2], ' ');
		//char *luca = path(cmds[0], env);
		cmd = ft_strjoin("/bin/", cmds[0]);
		execstat = execve(cmd, cmds, env);
		if (execstat == -1)
			puterror("dedneqknd");
	}
}

void	process2(char **argv, char **env, int fd[2], int y)
{
	
	char	**cmds;
	char 	*cmd;
	int		execstat;
	int		pid;

	pid = fork();
	if (pid < 0)
		puterror("Fork Error ");
	else if (pid == 0)
	{
		close(fd[1]);
		dup2(y, 1);
		dup2(fd[0], 0);
		cmds = ft_split(argv[3], ' '); 
		cmd = ft_strjoin("/usr/bin/", cmds[0]);
		execstat = execve(cmd, cmds, env);
		if (execstat == -1)
			puterror("Execve Error cdommand failed/not founded ");
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	x;
	int	y;

	x = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	y = open(argv[1], O_RDONLY);
	if (x < 0 || y < 0)
		return (0);
	if (argc != 5)
		return (0);
	if (pipe(fd) == -1)
		puterror("Pipe Error ");
	process1(argv, env, fd, y);
	wait(NULL);
	process2(argv, env, fd, x);
	close(fd[0]);
	close(fd[1]);
	return (0);
}