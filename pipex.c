/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:35:25 by rgeral            #+#    #+#             */
/*   Updated: 2021/12/21 13:30:00 by rgeral           ###   ########.fr       */
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

int main(int	argc, char	*argv[], char	*env[])
{
	char	**args;
	char	*tmp;
	int		status;
	int		i;

	i = 1;
	while (i < argc)
	{
		pid_t pid = fork();
		if (pid == -1) 
		{
			perror("fork");
			return EXIT_FAILURE;
		}
		else if(pid == 0)
		{
			args = ft_split(argv[i], ' ');
			tmp = ft_strjoin("/bin/", args[0]);
			free(args[0]);
			args[0] = tmp;
			execve(args[0], args, env);
		}
		else
		{
			wait(NULL);
			printf("done");
		}
		i++;
	}
	return(0);
}