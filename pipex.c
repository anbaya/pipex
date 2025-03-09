#include "pipex.h"

int execute(char *env, char *cd)
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
        printf("%s\n", full_cmd);
        if (access(full_cmd, X_OK) == 0 || ft_strchr(cd, '/'))
        {
            if (ft_strchr(cd, '/'))
                full_cmd = cd;
            execve(full_cmd, cmd, NULL);
            write (2, "Error:\nexecve error\n", 20);
            exit (1);
        }
        i++;
    }
    return (0);
}
int piping1(t_pipe *pipex, char **av)
{
    dup2 (pipex->fd_in, 0);
    dup2 (pipex->lbiba[1], 1);
    close (pipex->fd_in);
    close(pipex->lbiba[1]);
    close (pipex->fd_out);
    close(pipex->lbiba[0]);
    if (!execute(pipex->env, av[2]))
    {
        write (2, "Error:\ncmd1 is not executable !!\n", 33);
        return (2);
    }
    return (0);
}
int piping2(t_pipe *pipex, char **av)
{
    dup2 (pipex->lbiba[0], 0);
    dup2 (pipex->fd_out, 1);
    close (pipex->fd_out);
    close (pipex->fd_in);
    close (pipex->lbiba[1]);
    close (pipex->lbiba[0]);
    if (!execute(pipex->env, av[3]))
    {
        write (2, "Error:\ncmd2 is not executable !!\n", 33);
        return (2);
    }
    return (0);
}
int starting (t_pipe *pipex, int ac, char **av, char **envp)
{
    if (ac != 5 || !av[1] ||  !av[1][0]|| !av[2] ||  !av[2][0]
        || !av[3] ||  !av[3][0] || !av[4] ||  !av[4][0])
    {
        write (2, "Error:\ninvalid input\n", 21);
        return (1);
    }
    pipex->env = get_env(envp);
    pipex->fd_in = open(av[1], O_RDWR);
    pipex->fd_out = open(av[4], O_CREAT | O_RDWR);
    if (pipex->fd_in == -1 || pipex->fd_out == -1)
    {
        write (2, "Error:\nError while Opning files\n", 33);
        return (1);
    }
    if (ft_strchr(av[2], '/'))
        pipex->env = av[2];
    if (ft_strchr(av[3], '/'))
        pipex->env = av[3];
    pipe (pipex->lbiba);
    return (0);
}

int main(int ac, char **av, char **envp)
{
    t_pipe *pipex;

    pipex = malloc(sizeof(t_pipe));
    if (starting(pipex, ac, av, envp) != 0)
        exit(1);
    pipex->pid1 = fork();
    if (pipex->pid1 == 0)
        piping1(pipex, av);
    pipex->pid2 = fork();
    if (pipex->pid2 == 0)
        piping2(pipex, av);
    close (pipex->lbiba[0]);
    close (pipex->lbiba[1]);
    waitpid(pipex->pid1, NULL, 0);
    waitpid(pipex->pid2, NULL, 0);
    return(0);
}