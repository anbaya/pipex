# ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_pipe
{
    char *env;
    int pid1;
    int pid2;
    int c1_status;
    int c2_status;
    int fd_in;
    int fd_out;
    int lbiba[2];
}   t_pipe;


char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ftt_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char    **args_to_cmds(char *env, char **argv);
char    **cmds_split(char *env, char **av);
int     cmd_counter(char *env, char **av);
int     is_it_cmd(char *env, char *cd);
char    **sub_arr(char **arr, int n);
char    *get_env(char **av);
char    *get_path(char *av);

# endif