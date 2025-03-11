/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:11:17 by anbaya            #+#    #+#             */
/*   Updated: 2025/03/11 11:13:58 by anbaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipe
{
	char	*env;
	char	**paths;
	int		pid1;
	int		pid2;
	int		c1_status;
	int		c2_status;
	int		fd_in;
	int		fd_out;
	int		lpipe[2];
}			t_pipe;

char		*ft_strdup(const char *s);
char		**ft_split(const char *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strsjoin(char **strs);
char		*ftt_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
int			cmd_counter(char *env, char **av);
int			is_it_cmd(char *env, char *cd);
char		**sub_arr(char **arr, int n);
char		*get_env(char **av);
char		*get_path(char *av);
char		*to_str(char **av);
int			arrlen(char **av);
char		*get_cmd(char *arg, char *env);
void		free_arr(char **arr);
int			cut_for_norm(char **paths, char **cmd);
int			cut_for_norm2(char **paths, char **cmd, char *full_cmd);

#endif
