/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/07 11:33:51 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	execute_parent(char **commands, char **envp)
{
	char	**unix_path;
	char	*path;
	int		i;

	i = 0;
	unix_path = get_unix_path(envp, commands);
	while (unix_path[i])
	{
		path = get_path(unix_path[i], commands[0], unix_path, commands);
		if (access(path, X_OK) == 0)
		{
			if (execve(path, commands, envp) == -1)
			{
				free(path);
				handle_error(strerror(errno), errno, NULL);
			}
		}
		free(path);
		i++;
	}
	execve_fail(commands, unix_path, unix_path[i]);
	exit (EKEYEXPIRED);
}

void	handle_parent(char **argv, char **envp, int *fd)
{
	int		file_fd;
	char	**commands;

	file_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (file_fd == -1)
		handle_error(strerror(errno), errno, fd);
	close(fd[1]);
	if (dup2(file_fd, STDOUT_FILENO) == -1)
		handle_error(strerror(errno), errno, fd);
	close(file_fd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		handle_error(strerror(errno), errno, fd);
	close(fd[0]);
	commands = get_commands(argv[3]);
	if (access(commands[0], X_OK) == 0)
	{
		if (execve(commands[0], commands, envp) == -1)
			handle_error(strerror(errno), errno, NULL);
	}
	if (errno != ENOENT)
	{
		ptr_free(commands);
		handle_error(strerror(errno), errno, NULL);
	}
	execute_parent(commands, envp);
}

void	run_process(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		handle_error(strerror(errno), errno, NULL);
	pid = fork();
	if (pid < 0)
		handle_error(strerror(errno), errno, NULL);
	if (pid == 0)
		handle_child(argv, envp, fd);
	else
		handle_parent(argv, envp, fd);
}
