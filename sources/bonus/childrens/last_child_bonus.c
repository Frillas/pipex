/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:17:59 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/17 13:38:59 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/bonus/pipex_bonus.h"

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

static void	setup_fd(char *file, int *fd[2], t_list *data, int mode)
{
	int	file_fd;
	int	tot_pipes;

	tot_pipes = data->nb_pipes;
	file_fd = open(file, mode, 0664);
	if (file_fd == -1)
	{
		close(fd[tot_pipes - 1][0]);
		list_free(data);
		write(2, file, ft_strlen(file));
		write(2, ": ", 2);
		handle_error(strerror(errno), errno, NULL);
	}
	if ((dup2(file_fd, STDOUT_FILENO) == -1)
		|| (dup2(fd[tot_pipes - 1][0], STDIN_FILENO) == -1))
	{
		close(fd[tot_pipes - 1][0]);
		list_free(data);
		handle_error(strerror(errno), errno, NULL);
	}
	close(file_fd);
	close(fd[tot_pipes - 1][0]);
}

static void	handle_last(char **commands, char **envp, t_list *data, int i)
{
	char	**unix_path;
	char	*path;

	unix_path = get_unix_path(envp, commands);
	while (unix_path[i])
	{
		path = get_path(unix_path[i], commands[0], unix_path, commands);
		if (access(path, X_OK) == 0)
		{
			if (execve(path, commands, envp) == -1)
			{
				write_command(commands[0]);
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

static void	execute_last(char **cmds, char **envp, char **argv, t_list *data)
{
	if (!(access(cmds[0], X_OK)) || !(access(argv[data->nb_cmds + 1], X_OK)))
	{
		if (is_file(cmds) == TRUE)
		{
			if (execve(cmds[0], cmds, envp) == -1)
			{
				write_command(cmds[0]);
				list_free(data);
				ptr_free(cmds);
				handle_error(strerror(errno), errno, NULL);
			}
		}
		handle_last(cmds, envp, data, 0);
	}
	if (errno != ENOENT)
	{
		write_command(cmds[0]);
		list_free(data);
		ptr_free(cmds);
		handle_error(strerror(errno), 126, NULL);
	}
	handle_last(cmds, envp, data, 0);
}

void	last_child(int argc, char **argv, char **envp, t_list *data)
{
	char	**commands;
	int		append_mode;
	int		trunc_mode;

	append_mode = O_WRONLY | O_APPEND | O_CREAT;
	trunc_mode = O_WRONLY | O_TRUNC | O_CREAT;
	close_last_fds(data->fd, data->nb_pipes);
	if ((ft_strncmp("here_doc", argv[1], 9)) == 0)
		setup_fd(argv[argc - 1], data->fd, data, append_mode);
	else
		setup_fd(argv[argc - 1], data->fd, data, trunc_mode);
	commands = get_commands(argv[argc - 2]);
	execute_last(commands, envp, argv, data);
}
