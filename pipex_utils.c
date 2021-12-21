/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:59:36 by rgeral            #+#    #+#             */
/*   Updated: 2021/12/21 17:53:17 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
#include "pipex.h"

size_t	ft_split_count(char const *s, char c)
{
	size_t	count;
	size_t	i;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] == c && in_word)
			in_word = 0;
		if (s[i] != c && !in_word)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}

size_t	ft_word_len(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	free_all(char	**str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

char	**ft_pick_str(char	const *s, char c, char	**str_res, size_t	count)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = 0;
	while (j < count)
	{
		k = ft_word_len(&s[i], c);
		str_res[j] = ft_substr(&s[i], 0, k);
		if (!str_res[j])
		{
			free_all(str_res);
		}
		i += k;
		while (s[i] && s[i] == c)
			i++;
		j++;
	}
	return (str_res);
}

char	**ft_split(char const *s, char c)
{
	char	**str_res;
	size_t	w;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	w = ft_split_count(s, c);
	str_res = ((char **)malloc((w + 1) * sizeof(char *)));
	if (!str_res)
		return (NULL);
	str_res[w] = 0;
	ft_pick_str(&s[i], c, str_res, w);
	return (str_res);
}

size_t	ft_strlen(const char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(const char	*s, unsigned int start, size_t	len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (len > i && s[start])
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		res[i++] = s2[j++];
	}
	res[i] = '\0';
	return (res);
}

int	ft_memcmp(const void	*pointer1, const void	*pointer2, size_t	size)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)pointer1;
	p2 = (unsigned char *)pointer2;
	i = 0;
	while (i < size)
	{
		if (p1[i] != p2[i])
			return ((unsigned char)p1[i] - (unsigned char)p2[i]);
		i++;
	}
	return (0);
}