/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/03 22:50:04 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	execute_parent(char **argv, char **envp)
{
	char	**commands;
	char	**unix_path;
	char	*path;
	int		i;

	i = 0;
	commands = get_commands(argv[3]);
	if (access(argv[3], X_OK) == 0)
	{
		if (execve(argv[3], commands, envp) == -1)
			handle_error(strerror(errno));
	}
	unix_path = get_unix_path(envp, commands);
	while (unix_path[i])
	{
		path = get_path(unix_path[i], commands[0], unix_path, commands);
		if (access(path, X_OK) == 0)
		{
			if (execve(path, commands, envp) == -1)
				handle_error(strerror(errno));
			free(path);
			break ;
		}
		free(path);
		i++;
	}
	execve_fail(commands, unix_path, unix_path[i]);
	exit (EXIT_FAILURE);
}

void	handle_parent(char **argv, char **envp, int *fd)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		handle_error("dup2 error\n");
	}
	close(fd[0]);
	execute_parent(argv, envp);
}

void	execute_child(char **argv, char **envp)
{
	char	**commands;
	char	**unix_path;
	char	*path;
	int		i;

	i = 0;
	commands = get_commands(argv[2]);
	if (access(argv[2], X_OK) == 0)
	{
		if (execve(argv[2], commands, envp) == -1)
			handle_error(strerror(errno));
	}
	unix_path = get_unix_path(envp, commands);
	while (unix_path[i])
	{
		path = get_path(unix_path[i], commands[0], unix_path, commands);
		if (access(path, X_OK) == 0)
		{
			if (execve(path, commands, envp) == -1)
				handle_error(strerror(errno));
			free(path);
			break ;
		}
		free(path);
		i++;
	}
	execve_fail(commands, unix_path, unix_path[i]);
	exit (EXIT_FAILURE);
}

void	handle_child(char **argv, char **envp, int *fd)
{
	int	file_fd;

	file_fd = open(argv[1], O_RDONLY);
	if (file_fd == -1)
		handle_error("open error\n");
	close(fd[0]);
	if (dup2(file_fd, STDIN_FILENO) == -1)
		handle_error("dup2 error\n");
	close(file_fd);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		handle_error("dup2 error\n");
	close(fd[1]);
	execute_child(argv, envp);
}

void	run_process(char **argv, char **envp)
{
	int		status;
	int		fd[2];
	char	buffer[4096];
	pid_t	pid;

	if (pipe(fd) == -1)
		handle_error("pipe error\n");
	pid = fork();
	if (pid < 0)
		handle_error("fork error\n");
	if (pid == 0)
		handle_child(argv, envp, fd);
	if (waitpid(pid, &status, 0) < 0)
		handle_error("waitpid error\n");
	if (status)
	{
		close(fd[0]);
		close(fd[1]);
		exit(EXIT_FAILURE);
	}
	else
		handle_parent(argv, envp, fd);
}
