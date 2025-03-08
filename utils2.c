#include "pipex.h"

int is_it_cmd(char *env, char *cd)
{
    char **paths;
    char *full_cmd;
    char **cmd;
    int i;

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

int cmd_counter(char **av)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (av[i])
    {
        if (av[i])
            count++;
        i++;
    }
    return (count);
}

char	*ftt_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		size;
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
	str[i++] = ' ';
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}