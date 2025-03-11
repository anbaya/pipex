#include "pipex.h"

char **cmds_split(char *env, char **av)
{
    int i;
    int j;
    char *tmp;
    char **cmds;

    i = 0;
    j = 1;
    cmds = malloc(sizeof(char **) * cmd_counter(env, av));
    cmds[0] = av[0];
    while(av[++i])
    {
        while (av[i] && !is_it_cmd(env, av[i]))
        {
            tmp = ft_strjoin(cmds[j], av[i]);
            free (cmds[j]);
            cmds[j] = tmp;
            i++;
        }
        if (av[i] && j != 1)
            cmds[j + 1] = ft_strdup(av[i]);
        else if(av[i])
            cmds[j] = ft_strdup(av[i]);
        j++;
    }
	return (cmds);
}

char **args_to_cmds(char *env, char **argv)
{
	int		i;
	char	*tmp;
	char	*str;
	char 	**cmds;
	char	**args;

	if (!argv[0] || !argv[0][0])
	{
		write(2, "Error\n", 7);
		return (NULL);
	}
	i = 1;
	str = ft_strdup(argv[0]);
	while (argv[i])
	{
		tmp = ft_strsjoin((char *[]){str, "/", argv[i], NULL});
		free(str);
		if (!tmp || !argv[i][0])
			return (NULL);
		str = tmp;
		i++;
	}
	args = ft_split(str, ' ');
	cmds = cmds_split(env, args);
	return (free(str), free(args), cmds);
}
