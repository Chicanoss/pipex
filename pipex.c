/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:35:25 by rgeral            #+#    #+#             */
/*   Updated: 2022/01/28 14:24:30 by rgeral           ###   ########.fr       */
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

void	mario_pipe_lover(int *tube, int	*temp_tube, t_args *p, int nb)
{
	if (nb == 2)
		start_process(tube, temp_tube, p);
	else if (nb == p->argc - 2)
		end_process (tube, temp_tube, p);
	else
		progress_process (tube, temp_tube, p);
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

void	*do_child_not_war(t_args *p)
{
	int		i;
	int		tube[2];
	int		temp_tube[2];
	int		status;


	i = 1;
	p->j = 0;
	while (++i <= (p->argc - 1))
	{
		child_generator(tube, temp_tube, i, p);
		p->j++;
	}
	close(tube[0]);
	close(tube[1]);
	i = -1;
	while (++i < p->argc - 3)
		waitpid(p->pid[i], &status, 0);
	return (NULL);
}

int	main(int argc, char *argv[], char *env[])
{
	t_args	test;

	test.argv = argv;
	test.env = env;
	test.argc = argc;
	test.path = i_shall_path(env);
	test.j = 0;
	test.pid = malloc(sizeof(int) * argc - 3);

	if (!test.path)
		return ((int) NULL);
	do_child_not_war(&test);
	return (0);
}
