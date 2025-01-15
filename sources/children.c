/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:07:34 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/15 10:59:35 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static void	setup_fd_child(char *file, int *fd)
{
	int	file_fd;

	if (access(file, F_OK | R_OK) == 0)
	{
		file_fd = open(file, O_RDONLY);
		if (file_fd == -1)
		{
			write(2, file, ft_strlen(file));
			write(2, ": ", 2);
			handle_error(strerror(errno), errno, fd);
		}
		if (dup2(file_fd, STDIN_FILENO) == -1)
		{
			close(file_fd);
			handle_error(strerror(errno), errno, fd);
		}
		close(file_fd);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			handle_error(strerror(errno), errno, fd);
		close(fd[1]);
	}
	else
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			handle_error(strerror(errno), errno, fd);
		write(STDOUT_FILENO, "", 0);
		close(fd[1]);
		exit (EXIT_SUCCESS);
	}
}

static void	execute_child(char **commands, char **envp)
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
				ptr_free(commands);
				handle_error(strerror(errno), errno, NULL);
			}
		}
		free(path);
		i++;
	}
	execve_fail(commands, unix_path, unix_path[i]);
	exit (127);
}

static void	execute_command_child(char **cmds, char **envp, char **argv)
{
	if (!(access(cmds[0], X_OK)) || !(access(argv[2], X_OK)))
	{
		if (is_file(cmds) == TRUE)
		{
			if (execve(cmds[0], cmds, envp) == -1)
			{
				ptr_free(cmds);
				handle_error(strerror(errno), errno, NULL);
			}
		}
		execute_child(cmds, envp);
	}
	if (errno != ENOENT)
	{
		ptr_free(cmds);
		handle_error(strerror(errno), errno, NULL);
	}
	execute_child(cmds, envp);
}

void	handle_first_child(char **argv, char **envp, int *fd)
{
	char	**commands;

	close(fd[0]);
	setup_fd_child(argv[1], fd);
	commands = get_commands(argv[2]);
	execute_command_child(commands, envp, argv);
}
