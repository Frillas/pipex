/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:17:59 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/14 12:00:49 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

static void	close_last_fds(int *fd[2], int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (i == (nb_pipes - 1))
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

static void	execute_last(char **commands, char **envp, t_list *data)
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
				list_free(data);
				handle_error(strerror(errno), errno, NULL);
			}
		}
		free(path);
		i++;
	}
	execve_fail(commands, unix_path, unix_path[i]);
	list_free(data);
	exit (127);
}

void	setup_fd_here_doc(char *file, int *fd[2], int nb_pipes, t_list *data)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (file_fd == -1)
	{
		close(fd[nb_pipes - 1][0]);
		list_free(data);
		handle_error(strerror(errno), 2, NULL);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		close(fd[nb_pipes - 1][0]);
		list_free(data);
		handle_error(strerror(errno), errno, *fd);
	}
	close(file_fd);
	if (dup2(fd[nb_pipes - 1][0], STDIN_FILENO) == -1)
	{
		list_free(data);
		handle_error(strerror(errno), errno, *fd);
	}
	close(fd[nb_pipes - 1][0]);
}

void	setup_fd_last(char *file, int *fd[2], int nb_pipes, t_list *data)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (file_fd == -1)
	{
		close(fd[nb_pipes - 1][0]);
		list_free(data);
		handle_error(strerror(errno), 2, NULL);
	}
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		close(fd[nb_pipes - 1][0]);
		list_free(data);
		handle_error(strerror(errno), errno, *fd);
	}
	close(file_fd);
	if (dup2(fd[nb_pipes - 1][0], STDIN_FILENO) == -1)
	{
		list_free(data);
		handle_error(strerror(errno), errno, *fd);
	}
	close(fd[nb_pipes - 1][0]);
}

void	last_child(int argc, char **argv, char **envp, t_list *data)
{
	char	**cmds;

	close_last_fds(data->fd, data->nb_pipes);
	if ((ft_strncmp("here_doc", argv[1], 9)) == 0)
		setup_fd_here_doc(argv[argc - 1], data->fd, data->nb_pipes, data);
	else
		setup_fd_last(argv[argc - 1], data->fd, data->nb_pipes, data);
	cmds = get_commands(argv[argc - 2]);
	if (!(access(cmds[0], X_OK)) || !(access(argv[argc - 2], X_OK)))
	{
		if (is_file(cmds) == TRUE)
		{
			if (execve(cmds[0], cmds, envp) == -1)
			{
				list_free(data);
				ptr_free(cmds);
				handle_error(strerror(errno), errno, NULL);
			}
		}
		execute_last(cmds, envp, data);
	}
	if (errno != ENOENT)
	{
		list_free(data);
		ptr_free(cmds);
		handle_error(strerror(errno), 126, NULL);
	}
	execute_last(cmds, envp, data);
}
