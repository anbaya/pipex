#include "pipex.h"

int arrlen(char **av)
{
    int i;

    i = 0;
    while (av[i])
        i++;
    return (i);
}

char *to_str(char **av)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 1;
	str = ft_strdup(av[0]);
	while (av[i])
	{
		tmp = ftt_strjoin(str, av[i]);
		free(str);
		if (!tmp || !av[i][0])
			return (NULL);
		str = tmp;
		i++;
	}
    return (str);
}
char *get_path(char *av)
{
    int i;
    char **splited_av;
    char **tmp;
    char *path;

    i = 0;
    splited_av = ft_split(av, '/');
    tmp = sub_arr(splited_av, (arrlen(splited_av) - 1));
    path = to_str(tmp);
    free (tmp);
    return (path);
}
char *get_cmd(char *arg, char *env)
{
    int i;
    char **arr;
    char *cmd;

    i = 0;
    arr = ft_split(arg, '/');
    while (arr[i])
    {
        if (is_it_cmd(env, arr[i]))
        {
            cmd = ft_strdup(arr[i]);
            return(cmd);
        }
    }
}