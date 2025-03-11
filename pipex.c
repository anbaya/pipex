#include "pipex.h"

int execute(char *env, char *cd)
{
	char *full_cmd;
	char **paths;
	char **cmd;
	int i;
	cmd = ft_split(cd, ' ');
	paths = ft_split(env, ':');
	i = 0;
	if (ft_strchr(cmd[0], '/') || !env || !*env)
	{
		execve(cmd[0], cmd, NULL);
		perror("Error");
		free_arr(paths);
		free_arr(cmd);
		return (1);
	}
	while (paths && paths[i])
	{
		full_cmd = ft_strsjoin((char *[]){paths[i], "/", cmd[0], NULL});
		if (access(full_cmd, F_OK) == 0)
		{
			execve(full_cmd, cmd, NULL);
			perror("Error");
			free_arr(paths);
			free_arr(cmd);
			return (1);
		}
		free(full_cmd);
		i++;
	}
	write(2, "Error:\ncommand not found\n", 25);
	free_arr(paths);
	free_arr(cmd);
	return (1);
}
int piping1(t_pipe *pipex, char **av)
{
	dup2(pipex->fd_in, 0);
	close(pipex->fd_in);
	close(pipex->lbiba[0]);
	dup2(pipex->lbiba[1], 1);
	close(pipex->lbiba[1]);
	close(pipex->fd_out);
	if (!execute(pipex->env, av[2]))
	{
		write(2, "Error:\ncmd is not executable !!\n", 33);
		free(pipex->env);
		exit(2);
	}
	free(pipex->env);
	exit(0);
}
int piping2(t_pipe *pipex, char **av)
{
	dup2(pipex->lbiba[0], 0);
	dup2(pipex->fd_out, 1);
	close(pipex->fd_out);
	close(pipex->fd_in);
	close(pipex->lbiba[1]);
	close(pipex->lbiba[0]);
	if (!execute(pipex->env, av[3]))
	{
		write(2, "Error:\ncmd is not executable !!\n", 33);
		free(pipex->env);
		exit(2);
	}
	free(pipex->env);
	exit(0);
}
int starting(t_pipe *pipex, int ac, char **av, char **envp)
{
	if (ac != 5 || !av[1] || !av[1][0] || !av[2] || !av[2][0] || !av[3] || !av[3][0] || !av[4] || !av[4][0])
	{
		write(2, "Error:\ninvalid input\n", 21);
		return (1);
	}
	pipex->env = get_env(envp);
	pipex->fd_in = open(av[1], O_RDONLY);
	pipex->fd_out = open(av[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (pipex->fd_in == -1 || pipex->fd_out == -1)
	{
		write(2, "Error:\nError while opening files\n", 33);
		return (1);
	}
	pipe(pipex->lbiba);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_pipe pipex;

	pipex = (t_pipe){0};
	if (starting(&pipex, ac, av, envp) != 0)
	{
		free(pipex.env);
		exit(1);
	}
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		piping1(&pipex, av);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		piping2(&pipex, av);
	close(pipex.lbiba[0]);
	close(pipex.lbiba[1]);
	waitpid(pipex.pid2, NULL, 0);
	waitpid(pipex.pid1, NULL, 0);
	free(pipex.env);
	return (0);
}
