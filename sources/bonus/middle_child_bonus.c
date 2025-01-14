/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_child_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 09:47:45 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/14 16:27:15 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

static void	close_middle_fds(int *fd[2], int nb_pipes, int i)
{
	int	j;

	j = 0;
	while (j < nb_pipes)
	{
		if (j == i)
		{
			close(fd[j][0]);
			close(fd[j - 1][1]);
		}
		else
		{
			if (j != (i - 1))
				close(fd[j][0]);
			close(fd[j][1]);
		}
		j++;
	}
}

static void	setup_fd_mid(int *fd[2], int i)
{
	if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
		handle_error(strerror(errno), errno, NULL);
	close(fd[i - 1][0]);
	if (dup2(fd[i][1], STDOUT_FILENO) == -1)
		handle_error(strerror(errno), errno, NULL);
	close(fd[i][1]);
}

static void	handle_middle(char **commands, char **envp, t_list *data)
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

static void	execute_middle(char **cmds, char **envp, char **argv, t_list *data)
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
		handle_middle(cmds, envp, data);
	}
	if (errno != ENOENT)
	{
		list_free(data);
		ptr_free(cmds);
		handle_error(strerror(errno), errno, NULL);
	}
	handle_middle(cmds, envp, data);
}

void	middle_child(char **argv, char **envp, t_list *data, int i)
{
	char	**commands;

	close_middle_fds(data->fd, data->nb_pipes, i);
	setup_fd_mid(data->fd, i);
	commands = get_commands(argv[i + 2]);
	execute_middle(commands, envp, argv, data);
}
