/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:35:25 by rgeral            #+#    #+#             */
/*   Updated: 2021/12/23 17:06:47 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include "pipex.h"
#include <sys/types.h>
#include <sys/wait.h>

char	**i_shall_path(char	**env)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_memcmp(env[i], "PATH=", 5) == 0)
		{
			result = ft_split(&env[i][5], ':');
			while (result[j])
			{
				result[j] = ft_strjoin(result[j], "/");
				j++;
			}
			return (result);
		}
		i++;
	}
	return (NULL);
}

void	mario_pipe_lover(int *tube, t_args *p, int nb)
{
	int	file;

	if (nb == 2)
	{
		file = open(p->argv[1], 0);
		close(tube[0]);
		dup2(tube[1], 1);
		dup2(file, 0);
		close(tube[1]);
		close(file);
	}
	else
	{
		file = open(p->argv[4], O_CREAT | O_TRUNC | O_WRONLY);
		close(tube[1]);
		dup2(tube[0], 0);
		dup2(file, 1);
		close(tube[0]);
		close(file);
	}
}

void	*care_child(t_args *p, int nb, int *tube)
{
	char	*tmp;
	int		j;
	char	**args;

	j = 0;
	mario_pipe_lover(tube, p, nb);
	args = ft_split(p->argv[nb], ' ');
	while (p->path[j])
	{	
		tmp = ft_strjoin(p->path[j], args[0]);
		if (access(tmp, F_OK | X_OK) == 0)
			break ;
		free(tmp);
		tmp = NULL;
		j++;
	}
	if (tmp)
	{
		free(args[0]);
		args[0] = tmp;
		execve(args[0], args, p->env);
	}
	free(args);
	return (NULL);
}

void	*do_child_not_war(t_args	*p)
{
	int		i;
	int		tube[2];
	int		status;
	pid_t	pid;

	i = 1;
	pipe(tube);
	while (i++ < p->argc - 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (NULL);
		}
		else if (pid == 0)
			care_child(p, i, tube);
	}
	close(tube[0]);
	close(tube[1]);
	i = -1;
	while (i++ < 2)
		wait(&status);
	return (NULL);
}

int	main(int argc, char *argv[], char *env[])
{
	int		i;
	int		tube[2];
	int		fd;
	int		status;
	t_args	test;

	test.argv = argv;
	test.env = env;
	test.argc = argc;
	if (argc != 5)
		return (printf("Il faut 5 args\n") * 0);
	test.path = i_shall_path(env);
	if (!test.path)
		return ((int) NULL);
	do_child_not_war(&test);
	return (0);
}
