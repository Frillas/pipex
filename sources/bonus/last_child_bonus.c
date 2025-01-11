/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:17:59 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/11 17:36:41 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

void	close_last_fds(int fd[][2], int nb_fd)
{
	int	i;

	i = 0;
	while (i < nb_fd)
	{
		if (i == (nb_fd - 1))
		{
			close(fd[i][1]);
		}
		else
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
		i++;
	}
}

void	execute_parent(char **commands, char **envp, int fd)
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
				handle_error(strerror(errno), errno, fd);
			}
		}
		free(path);
		i++;
	}
	execve_fail(commands, unix_path, unix_path[i]);
	close(fd);
	exit (127);
}

int	setup_fd_parent(char *file, int fd[][2], int nb_fd)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (file_fd == -1)
		handle_error(strerror(errno), 2, fd);
	if (dup2(file_fd, STDOUT_FILENO) == -1)
		handle_error(strerror(errno), errno, fd);
	close(file_fd);
	if (dup2(fd[nb_fd - 1][0], STDIN_FILENO) == -1)
		handle_error(strerror(errno), errno, fd);
	close(fd[0]);
	return (file_fd);
}

void	last_child(int argc, char **argv, char **envp, int **fd)
{
	char	**cmds;
	int		file_fd;

	close_last_fds(fd, (argc - 4));
	file_fd = setup_fd_parent(argv[argc - 1], fd, argc - 4);
	cmds = get_commands(argv[argc - 2]);
	if (access(cmds[0], X_OK) == 0)
	{
		if (is_file(cmds) == TRUE)
		{
			if (execve(cmds[0], cmds, envp) == -1)
				handle_error(strerror(errno), errno, &file_fd);
		}
		ptr_free(cmds);
		handle_error("Command not found", 127, &file_fd);
	}
	if (errno != ENOENT)
	{
		ptr_free(cmds);
		handle_error(strerror(errno), 126, &file_fd);
	}
	execute_parent(cmds, envp, file_fd);
}
