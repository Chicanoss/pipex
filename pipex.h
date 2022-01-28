/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:03:31 by rgeral            #+#    #+#             */
/*   Updated: 2022/01/27 15:46:14 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_arguments
{
	char	**argv;
	char	**path;
	char	**env;
	int		argc;
	pid_t	*pid;
	int		j;
}				t_args;

char	**ft_split(char const *s, char c);
int 	main(int	argc, char	*argv[], char	*env[]);
char	*ft_substr(const char	*s, unsigned int start, size_t	len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char	*str);
int		ft_memcmp(const void	*pointer1, const void	*pointer2, size_t	size);
void	start_process(int *tube,int	*temp_tube, t_args *p);
void	progress_process (int *tube,int	*temp_tube, t_args *p);
void	end_process (int	*tube, int	*temp_tube, t_args	*p);
int		child_generator (int *tube, int	*temp_tube, int i, t_args *p);
void	*care_child(t_args *p, int nb, int *tube, int	*temp_tube);

#endif