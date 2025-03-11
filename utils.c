/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:14:44 by anbaya            #+#    #+#             */
/*   Updated: 2025/03/11 11:15:02 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc((sizeof(char) * i) + 1);
	if (!str)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * size + 2);
	if (!str)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_strsjoin(char **strs)
{
	char	*str;
	size_t	total_len;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!strs || !*strs)
		return (NULL);
	total_len = 0;
	i = -1;
	while (strs[++i])
		total_len += ft_strlen(strs[i]);
	str = malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	k = -1;
	while (strs[++i])
	{
		j = -1;
		while (strs[i][++j])
			str[++k] = strs[i][j];
	}
	str[++k] = 0;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	j;
	char	*r;

	r = (char *)s;
	j = ft_strlen(s);
	i = 0;
	while (i <= j)
	{
		if (r[i] == c)
			return (r + i);
		i++;
	}
	return (0);
}
