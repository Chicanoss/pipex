/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:35:25 by rgeral            #+#    #+#             */
/*   Updated: 2021/12/21 18:43:25 by rgeral           ###   ########.fr       */
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
	int	i;
	int	j;
	char	**result;

	i = 0;
	j = 0;
	while(env[i])
	{
		if(ft_memcmp(env[i], "PATH=", 5) == 0)
		{
			result = ft_split(&env[i][5], ':');
			while(result[j])
			{
				result[j] = ft_strjoin(result[j], "/");
				j++;
			}
			return(result);
		}
		i++;
	}
	return(NULL);
}

void	*care_child(char	**path, char	**argv, char	**env)
{
	char	*tmp;
	int		i;
	int		j;
	char	**args;

	i = 1;
	j = 0;
	
	while (path[j])
	{	
		args = ft_split(argv[i], ' ');
		tmp = ft_strjoin(path[j], args[0]);
		free(args[0]);
		args[0] = tmp;
		execve(args[0], args, env);
		j++;
	}
	return(NULL);
		
}

int main(int	argc, char	*argv[], char	*env[])
{
	int		i;
	char	**path;

	i = 1;
	path = i_shall_path(env);
	while (i < argc)
	{
		pid_t pid = fork();
		if (pid == -1) 
		{
			perror("fork");
			return EXIT_FAILURE;
		}
		else if(pid == 0)
			care_child(path, argv, env);
		else
			wait(NULL);
		i++;
	}
	return(0);
}