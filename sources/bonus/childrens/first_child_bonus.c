/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:42:16 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/16 09:05:46 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/bonus/pipex_bonus.h"

static void	close_first_fds(int *fd[2], int nb_fd, char *limiter)
{
	int	j;

	j = 0;
	while (j < nb_fd)
	{
		if ((j == 0) && (ft_strncmp("here_doc", limiter, 9)) != 0)
			close(fd[j][0]);
		else if (j != 0)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		j++;
	}
}

static void	handle_first(char **commands, char **envp, t_list *data)
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
	list_free(data);
	execve_fail(commands, unix_path, unix_path[i]);
	exit (127);
}

static void	execute_first(char **cmds, char **envp, char **argv, t_list *data)
{
	if (!(access(cmds[0], X_OK)) || !(access(argv[2], X_OK)))
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
		handle_first(cmds, envp, data);
	}
	if (errno != ENOENT)
	{
		list_free(data);
		ptr_free(cmds);
		handle_error(strerror(errno), errno, NULL);
	}
	handle_first(cmds, envp, data);
}

static void	setup_fd_child(char *file, int *fd[2], t_list *data)
{
	int	file_fd;

	file_fd = 0;
	if (access(file, F_OK | R_OK) == 0)
	{
		file_fd = open(file, O_RDONLY);
		if (file_fd == -1)
			fd_error(strerror(errno), fd, data, file_fd);
		if ((dup2(file_fd, STDIN_FILENO) == -1)
			|| (dup2(fd[0][1], STDOUT_FILENO) == -1))
			fd_error(strerror(errno), fd, data, file_fd);
		close(file_fd);
		close(fd[0][1]);
	}
	else
	{
		if (dup2(data->fd[0][1], STDOUT_FILENO) == -1)
			fd_error(strerror(errno), fd, data, file_fd);
		write(STDOUT_FILENO, "", 0);
		close(data->fd[0][1]);
		list_free(data);
		exit (EXIT_SUCCESS);
	}
}

void	first_child(char **argv, char **envp, t_list *data)
{
	char	**commands;

	commands = NULL;
	close_first_fds(data->fd, data->nb_pipes, argv[1]);
	if ((ft_strncmp("here_doc", argv[1], 9)) == 0)
		setup_here_doc(argv[2], data->fd, data);
	else
	{
		setup_fd_child(argv[1], data->fd, data);
		commands = get_commands(argv[2]);
		execute_first(commands, envp, argv, data);
	}
}
