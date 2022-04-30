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

static char	*find_path(char **envp, char *cmd)
{
	char	**paths;
	char	*cmd_path;
	char	*sub;

	cmd = *ft_split(cmd, ' ');
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	sub = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
	paths = ft_split(sub, ':');
	free(sub);
	sub = ft_strjoin("/", cmd);
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, sub);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
			break ;
		free(cmd_path);
		paths++;
	}
	free(sub);
	free(cmd);
	return (cmd_path);
}

void	process2(char **argv, char **env, int fd[2], int y)
{
	char	**cmds;
	char	*cmd;
	int		execstat;
	int		pid;

	pid = fork();
	if (pid < 0)
		puterror("In process, Fork Error ");
	else if (pid == 0)
	{
		close(fd[1]);
		dup2(y, 1);
		dup2(fd[0], 0);
		cmds = ft_split(argv[3], ' ');
		cmd = find_path(env, argv[3]);
		execstat = execve(cmd, cmds, env);
		if (execstat == -1)
			puterror("Execve Error cdommand failed/not founded ");
	}
}

void	process1(char **argv, char **env, int fd[2], int x)
{
	int		execstat;
	int		pid;
	char	**cmds;
	char	*cmd;

	pid = fork();
	if (pid < 0)
		puterror("In process, Fork Error ");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(x, 0);
		cmds = ft_split(argv[2], ' ');
		cmd = find_path(env, argv[2]);
		execstat = execve(cmd, cmds, env);
		if (execstat == -1)
			puterror("Execve Error command failed/not founded");
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	x;
	int	y;

	x = open(argv[1], O_RDONLY);
	y = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (x < 0 || y < 0)
	{
		write(1, "zsh: no such file or directory: ", 28);
		write(1, argv[1], ft_strlen(argv[1]));
		write(1, "\n", 1);
		return (0);
	}	
	if (argc != 5)
		return (0);
	if (pipe(fd) == -1)
		puterror("Pipe Error ");
	process1(argv, env, fd, x);
	wait(NULL);
	process2(argv, env, fd, y);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
