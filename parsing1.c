#include "pipex.h"

char **cmds_split(char **av)
{
    int i;
    int j;
    char *tmp;
    char **cmds;

    i = 0;
    j = 1;
    cmds = malloc(sizeof(char **) * cmd_counter(av));
    cmds[0] = av[0];
    while(av[++i])
    {
        while (av[i] && !is_cmd(av[i]))
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
}

char **args_to_cmds(char **argv)
{
	int		i;
	char	*tmp;
	char	*str;
	char	**args;

	if (!argv[0] || !argv[0][0])
	{
		write(2, "Error\n", 7);
		return (NULL);
	}
	i = 0;
	str = ftt_strdup(argv[i]);
	i++;
	while (argv[i])
	{
		tmp = ftt_strjoin(str, argv[i]);
		free(str);
		if (!tmp || !argv[i][0])
			return (NULL);
		str = tmp;
		i++;
	}
	args = ft_split(str, ' ');
	free(str);
	return (args);
}