#include "pipex.h"

int	check_file(char *file, int code)
{
	if (code == 0)
	{
		if (access(file, F_OK))
		{
			perror(file);
			return (0);
		}
		return (open(file, O_RDONLY));
	}
	else
		return (open(file, O_RDWR | O_CREAT | O_NOCTTY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
}

void	run(char *arg, char **path, char **envp)
{
	char **cmd_and_flags;
	char *correct_cmd;

	cmd_and_flags = ft_split(arg, ' ');
	correct_cmd = get_correct_cmd(path, cmd_and_flags);
	if (execve(correct_cmd, cmd_and_flags, envp) == -1)
	{
		write(2, "Command execution failed\n", 25);
		exit(EXIT_FAILURE);
	}
	free(correct_cmd);
	free_tab(cmd_and_flags);
}

void	pipex(char **av, char **envp)
{
	char	**path;
	int		pipe_fd[2];
	int		pid;

	pipe(pipe_fd);
	pid = fork();
	path = get_all_path(envp);
	if (!pid)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		run(av[2], path, envp);
		waitpid(pid, NULL, 0);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	run(av[3], path, envp);
	free_tab(path);
}

int main(int ac, char *av[], char *envp[])
{
	int	infile_fd;
	int	outfile_fd;
	
	if (ac == 5)
	{
		infile_fd = check_file(av[1], 0);
		outfile_fd = check_file(av[4], 1);
		dup2(infile_fd, 0);
		dup2(outfile_fd, 1);
		pipex(av, envp);
	}
	else
		perror("Bad number of arguments");
	return (0);
}
