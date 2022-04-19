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

void	process1(char **argv, char **env, int fd[2])
{
	int		pid1 = fork();
	char	**cmds;
	if (pid1 < 0)
	{
		perror("ocio");
		exit(1);
	}
	else if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		char	*cmds[] = {"echo", "loooool\nlonzolol", 0};
		execve("/bin/echo", cmds, env);
	}
}

void	process2(char **argv, char **env, int fd[2])
{
	int		pid2 = fork();
	char	**cmds;// = {"grep", "lon", 0};
	if (pid2 < 0)
	{
		perror("ocio");
		exit(1);
	}
	else if (pid2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		//char* cmds[] = {"grep", "lon", 0};
		execve("/usr/bin/grep", cmds, env);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	/*if (argc != 5)
		return (0);*/
	if (pipe(fd) == -1)
		return (0);
	process1(argv, env, fd);
	process2(argv, env, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}
