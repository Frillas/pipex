/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:07:34 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/05 12:04:04 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	execute_child(char **commands, char **envp)
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
				handle_error(strerror(errno), errno);
			}
			break ;
		}
		free(path);
		i++;
	}
	execve_fail(commands, unix_path, unix_path[i]);
	exit (ENOENT);
}

void	setup_fd_child(char *file, int *fd)
{
	int	file_fd;

	if (access(file, F_OK | R_OK) == 0)
	{
		file_fd = open(file, O_RDONLY);
		if (file_fd == -1)
			handle_error(strerror(errno), errno);
		if (dup2(file_fd, STDIN_FILENO) == -1)
			handle_error(strerror(errno), errno);
		close(file_fd);
	}
	else
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			handle_error(strerror(errno), errno);
		write(STDOUT_FILENO, "", 0);
		close(fd[1]);
		exit (EXIT_SUCCESS);
	}
}

void	execute_command_child(char **commands, char **envp, char **argv)
{
	if (access(argv[2], X_OK) == 0)
	{
		if (execve(argv[2], commands, envp) == -1)
			handle_error(strerror(errno), errno);
	}
	if (access(commands[0], X_OK) == 0)
	{
		if (execve(commands[0], commands, envp) == -1)
			handle_error(strerror(errno), errno);
	}
	execute_child(commands, envp);
}

void	handle_child(char **argv, char **envp, int *fd)
{
	int		file_fd;
	char	**commands;

	close(fd[0]);
	setup_fd_child(argv[1], fd);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		handle_error(strerror(errno), errno);
	close(fd[1]);
	commands = get_commands(argv[2]);
	execute_command_child(commands, envp, argv);
}
