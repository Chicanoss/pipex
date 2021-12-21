/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:03:31 by rgeral            #+#    #+#             */
/*   Updated: 2021/12/21 16:08:18 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

char	**ft_split(char const *s, char c);
int 	main(int	argc, char	*argv[], char	*env[]);
char	*ft_substr(const char	*s, unsigned int start, size_t	len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char	*str);
int		ft_memcmp(const void	*pointer1, const void	*pointer2, size_t	size);

#endif