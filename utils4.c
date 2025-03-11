/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:18:03 by anbaya            #+#    #+#             */
/*   Updated: 2025/03/11 11:18:27 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cut_for_norm(char **paths, char **cmd)
{
	execve(cmd[0], cmd, NULL);
	perror("Error");
	free_arr(paths);
	free_arr(cmd);
	return (1);
}

int	cut_for_norm2(char **paths, char **cmd, char *full_cmd)
{
	execve(full_cmd, cmd, NULL);
	perror("Error");
	free_arr(paths);
	free_arr(cmd);
	return (1);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
