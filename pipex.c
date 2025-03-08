#include "pipex.h"

char *get_env(char **av)
{
    int i;

    i = 0;
    while (av[i])
    {
        if (ft_strncmp(av[i], "PATH", 4) == 0)
        {
            return (ft_strdup(av[i] + 5));
            exit(0);
        }
        i++;
    }
    return (0);
}

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

int main(int ac, char **av, char **envp)
{
    char *env;
    int pid1;
    int pid2;
    int c_status;
    int fd_in;
    int fd_out;
    int lbiba[2];

    if (ac != 5 || !av[1] ||  !av[1][0]|| !av[2] ||  !av[2][0]
        || !av[3] ||  !av[3][0] || !av[4] ||  !av[4][0])
    {
        write (2, "Error:\ninvalid input\n", 21);
        return (1);
    }
    env = get_env(envp);
    fd_in = open(av[1], O_RDWR);
    fd_out = open(av[4], O_CREAT | O_RDWR);
    if (fd_in == -1 || fd_out == -1)
    {
        write (2, "Error:\nError while Opning files\n", 33);
        return (1);
    }
    if (ft_strchr(av[2], '/'))
        env = av[2];
    if (ft_strchr(av[3], '/'))
        env = av[3];
    pipe (lbiba);
    pid1 = fork();
    if (pid1 == 0)
    {
        dup2 (fd_in, 0);
        dup2 (lbiba[1], 1);
        close (fd_in);
        close(lbiba[1]);
        close (fd_out);
        close(lbiba[0]);
        if (!execute(env, av[2]))
        {
            write (2, "Error:\ncmd1 is not executable !!\n", 33);
            return (2);
        }

    }
    fork();
    if (pid2 == 0)
    {
        dup2 (lbiba[0], 0);
        dup2 (fd_out, 1);
        close (fd_out);
        close (fd_in);
        close (lbiba[1]);
        close (lbiba[0]);
        if (!execute(env, av[3]))
        {
            write (2, "Error:\ncmd2 is not executable !!\n", 33);
            return (2);
        }
    }
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return(0);
}