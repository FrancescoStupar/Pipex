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

void	process1(char **argv, char **env, int fd[2], int y)
{
	char *cmd;
	char **cmds;
	int		pid = fork();
	
	cmd = NULL;
	cmds = NULL;
	if (pid < 0)
	{
		perror("ocio");
		exit(1);
	}
	else if (pid == 0)
	{
		if (dup2(y, 0) == -1)
			perror("ERROwsR");
		if(dup2(fd[1], 1) == -1)
			perror("ERROswR");
		close(fd[0]);
		cmds = ft_split(argv[2], ' ');
		cmd = ft_strjoin("/usr/bin/", cmds[0]);
		execve(cmd, cmds, env);
	}
}

void	process2(char **argv, char **env, int fd[2], int x)
{
	
	char *cmd;
	char	**cmds;
	int		pid = fork();

	cmd = NULL;
	cmds = NULL;
	
	
	if (pid < 0)
	{
		perror("ocio");
		exit(1);
	}
	else if (pid == 0)
	{

		if (dup2(x, 1) == -1)
			perror("ERROswswR");
		if (dup2(fd[0], 0) == -1)
			perror("ERROswR");	
		close(fd[1]);
		cmds = ft_split(argv[3], ' ');
		cmd = ft_strjoin("/usr/bin/", cmds[0]);
		execve(cmd, cmds, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int x;
	int y;

	x = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	y = open(argv[1], O_RDONLY);
	if (x < 0 || y < 0)
		return (0);
	if (argc != 5)
		return (0);
	if (pipe(fd) == -1)
		return (0);
	process1(argv, env, fd, y);
	process2(argv, env, fd, x);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}
