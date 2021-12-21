/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:35:25 by rgeral            #+#    #+#             */
/*   Updated: 2021/12/21 16:37:22 by rgeral           ###   ########.fr       */
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


char	*i_shall_pass(char	**env)
{
	int	i;
	char	**result;

	i = 0;
	while(env[i])
	{
		if(ft_memcmp(env[i], "PATH=", 5) == 0)
		{
			result = ft_split(&env[i][5], ':');
			printf("%s\n", result[0]);

			return(&env[i][5]);
		}
		i++;
	}
	return(NULL);

}

int main(int	argc, char	*argv[], char	*env[])
{
	char	**args;
	char	*tmp;
	int		i;
	char	*path;

	i = 1;
	path = i_shall_pass(env);
	printf("%s\n", path);
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