/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/07 18:27:36 by aroullea         ###   ########.fr       */
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

void	setup_fd_parent(char *file, int *fd)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (file_fd == -1)
		handle_error(strerror(errno), errno, fd);
	close(fd[1]);
	if (dup2(file_fd, STDOUT_FILENO) == -1)
		handle_error(strerror(errno), errno, fd);
	close(file_fd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		handle_error(strerror(errno), errno, fd);
	close(fd[0]);
}

void	handle_parent(char **argv, char **envp, int *fd)
{
	int		file_fd;
	char	**cmds;

	setup_fd_parent(argv[4], fd);
	file_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	cmds = get_commands(argv[3]);
	if (access(cmds[0], X_OK) == 0)
	{
		if (cmds[0][0] == '/' || (cmds[0][0] == '.' && cmds[0][1] == '/'))
		{
			if (execve(cmds[0], cmds, envp) == -1)
				handle_error(strerror(errno), errno, NULL);
		}
		handle_error("Command not found", 127, NULL);
	}
	if (errno != ENOENT)
	{
		ptr_free(cmds);
		handle_error(strerror(errno), errno, NULL);
	}
	execute_parent(cmds, envp);
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
