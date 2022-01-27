/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:35:25 by rgeral            #+#    #+#             */
/*   Updated: 2022/01/18 17:03:50 by rgeral           ###   ########.fr       */
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

void	mario_pipe_lover(int *tube,int	*temp_tube, t_args *p, int nb)
{
	int	file;

	if (nb == 2)
	{
		file = open(p->argv[1], 0);
		close(tube[0]);
		dup2(temp_tube[1], 1);
		dup2(file, 0);
		close(temp_tube[1]);
		close(file);
	}
	else if (nb == p->argc - 2)
	{
		file = open(p->argv[p->argc - 1], O_CREAT | O_TRUNC | O_WRONLY);
		close(tube[1]);
		dup2(tube[0], 0);
		dup2(file, 1);
		close(tube[1]);
		close(file);
	}
	else
	{
		dup2(tube[0], 0);
		dup2(temp_tube[1], 1);
		close(tube[0]);
		close(tube[1]);
		close(temp_tube[0]);
		close(temp_tube[1]);
	}

}

void	*care_child(t_args *p, int nb, int *tube, int	*temp_tube)
{
	char	*tmp;
	int		j;
	char	**args;

	j = 0;
	mario_pipe_lover(tube, temp_tube, p, nb);
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
	int		temp_tube[2];
	int		status;
	pid_t	pid;

	i = 1;
	while (i++ <= p->argc - 1)
	{
		// pipe sauf si dernier tour
		if (i != p->argc - 1)
		{
			pipe(temp_tube);
		}
		/*if (i != 2)
		{
			pipe(temp_tube);
		}*/
		
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return (NULL);
		}
		else if (pid == 0)
			care_child(p, i, tube, temp_tube);
		if (i > 2)
		{
			close(tube[0]);
			close(tube[1]);
		}
		tube[0] = temp_tube[0];
		tube[1] = temp_tube[1];
		//tube[0] = temp_tube[0];
		// fermer pipe du tour precedent sauf si premier tour
		// mettre les ints de pipe2 dans pipe 1
		//pipe1[0] = pipe2[0];
		//[1]
	}
	close(tube[0]);
	close(tube[1]);
	i = -1;
	while (i++ < p->argc - 3)
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
	
	printf("Il y a %d args\n", argc);
	test.path = i_shall_path(env);
	if (!test.path)
		return ((int) NULL);
	do_child_not_war(&test);
	return (0);
}
