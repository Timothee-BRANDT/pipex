/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:31:04 by tbrandt           #+#    #+#             */
/*   Updated: 2022/05/06 12:08:19 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file(char *file, int code)
{
	if (code == 0)
	{
		if (access(file, R_OK) || access(file, W_OK) || access(file, X_OK))
			return (-2);
		if (access(file, F_OK) == -1)
		{
			perror(file);
			exit(EXIT_FAILURE);
		}
		return (open(file, O_RDONLY));
	}
	else
		return (open(file, O_RDWR | O_CREAT | O_NOCTTY | \
		O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
}

void	run(char *arg, char **path, char **envp)
{
	char	**cmd_and_flags;
	char	*correct_cmd;

	cmd_and_flags = ft_split(arg, ' ');
	correct_cmd = get_correct_cmd(path, cmd_and_flags);
	if (!correct_cmd)
	{
		free_tab(cmd_and_flags);
		write(2, "zsh: command not found.\n", 24);
		exit(EXIT_FAILURE);
	}
	if (execve(correct_cmd, cmd_and_flags, envp) == -1)
		write(2, "Command execution failed\n", 25);
	free_tab(cmd_and_flags);
	free(correct_cmd);
	exit(EXIT_FAILURE);
}

void	close_and_dup(int pipe_fd, int pipe_fd1, int code)
{
	if (code == 0)
	{
		close(pipe_fd);
		dup2(pipe_fd1, 1);
		close(pipe_fd1);
	}
	else
	{
		close(pipe_fd1);
		dup2(pipe_fd, 0);
		close(pipe_fd);
	}
}

void	pipex(char **av, char **envp)
{
	char	**path;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(pipe_fd);
	path = get_all_path(envp);
	pid1 = fork();
	if (pid1 == 0)
	{
		close_and_dup(pipe_fd[0], pipe_fd[1], 0);
		run(av[2], path, envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close_and_dup(pipe_fd[0], pipe_fd[1], 1);
		run(av[3], path, envp);
	}
	free_tab(path);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int ac, char *av[], char *envp[])
{
	int	infile_fd;
	int	outfile_fd;

	if (ac == 5)
	{
		infile_fd = check_file(av[1], 0);
		if (infile_fd == -2)
		{
			write(2, "zsh: permission denied.\n", 24);
			exit(EXIT_FAILURE);
		}
		outfile_fd = check_file(av[4], 1);
		dup2(infile_fd, 0);
		dup2(outfile_fd, 1);
		pipex(av, envp);
		close(infile_fd);
		close(outfile_fd);
	}
	else
		write(2, "Bad number of arguments.\n", 25);
	return (0);
}
