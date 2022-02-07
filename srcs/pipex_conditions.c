/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_conditions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:35:25 by rgeral            #+#    #+#             */
/*   Updated: 2022/02/07 12:32:47 by rgeral           ###   ########.fr       */
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
	if (i != p->argc - 1)
	{
		if (pipe(temp_tube) == -1)
			perror("pipe is riped\n");
	}
	p->pid[p->j] = fork();
	if (p->pid[p->j] == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (p->pid[p->j] == 0)
	{	
		care_child(p, i, tube, temp_tube);
	}
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

void	progress_process(int *tube, int	*temp_tube)
{
	ft_dup2(tube[0], 0);
	ft_dup2(temp_tube[1], 1);
	close(tube[0]);
	close(tube[1]);
	close(temp_tube[0]);
	close(temp_tube[1]);
}

void	end_process(int	*tube, t_args	*p)
{
	int	file;

	file = open(p->argv[p->argc - 1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	close(tube[1]);
	ft_dup2(tube[0], 0);
	ft_dup2(file, 1);
	close(tube[1]);
	close(file);
}
