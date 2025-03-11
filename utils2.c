/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:19:08 by anbaya            #+#    #+#             */
/*   Updated: 2025/03/11 11:19:11 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_strncmp(av[i], "PATH", 4) == 0)
			return (ft_strdup(av[i] + 5));
		i++;
	}
	return (0);
}

char	**sub_arr(char **arr, int n)
{
	int		i;
	char	**arg;

	i = 0;
	arg = malloc(sizeof(char *) * (n + 1));
	while (i < n)
	{
		arg[i] = ft_strdup(arr[i]);
		i++;
	}
	return (arg);
}

int	is_it_cmd(char *env, char *cd)
{
	char	**paths;
	char	*full_cmd;
	char	**cmd;
	int		i;

	paths = ft_split(env, ':');
	cmd = ft_split(cd, ' ');
	i = 0;
	while (paths[i])
	{
		full_cmd = ft_strjoin(ft_strjoin(paths[i], "/"), cmd[0]);
		if (access(full_cmd, X_OK) == 0 || ft_strchr(cd, '/'))
			return (1);
		i++;
	}
	return (0);
}

int	cmd_counter(char *env, char **av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (av[i])
	{
		if (is_it_cmd(env, av[i]))
			count++;
		i++;
	}
	return (count);
}
