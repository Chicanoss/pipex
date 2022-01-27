/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_conditions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:35:25 by rgeral            #+#    #+#             */
/*   Updated: 2022/01/27 12:58:48 by rgeral           ###   ########.fr       */
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

int	child_generator(int *tube, int	*temp_tube, int i, t_args *p)
{
	pid_t	pid;

	if (i != p->argc - 1)
	{
		pipe(temp_tube);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ((int) NULL);
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
	return (1);
}

int	ft_dup2(int a, int b)
{
	int	fd;

	fd = dup2(a, b);
	if (fd == -1)
		return (printf("error"));
	return (fd);
}

void	start_process(int *tube, int	*temp_tube, t_args *p)
{
	int	file;

	file = open(p->argv[1], 0);
	close(tube[0]);
	ft_dup2(temp_tube[1], 1);
	ft_dup2(file, 0);
	close(temp_tube[1]);
	close(file);
}

void	progress_process(int *tube, int	*temp_tube, t_args *p)
{
	ft_dup2(tube[0], 0);
	ft_dup2(temp_tube[1], 1);
	close(tube[0]);
	close(tube[1]);
	close(temp_tube[0]);
	close(temp_tube[1]);
}

void	end_process(int	*tube, int	*temp_tube, t_args	*p)
{
	int	file;

	file = open(p->argv[p->argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	close(tube[1]);
	ft_dup2(tube[0], 0);
	ft_dup2(file, 1);
	close(tube[1]);
	close(file);
}
