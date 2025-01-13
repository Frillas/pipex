/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:42:16 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/13 18:15:41 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

static void	close_child_fds(int *fd[2], int nb_fd, char *limiter)
{
	int	j;

	j = 0;
	while (j < nb_fd)
	{
		if ((j == 0) && (ft_strncmp("here_doc", limiter, 9)) != 0)
			close(fd[j][0]);
		else
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		j++;
	}
}

static void	execute_child(char **commands, char **envp, t_list *data)
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

static void	setup_fd_child(char *file, int *fd[2], t_list *data)
{
	int	file_fd;

	if (access(file, F_OK | R_OK) == 0)
	{
		file_fd = open(file, O_RDONLY);
		if (file_fd == -1)
			handle_error(strerror(errno), errno, NULL);
		if (dup2(file_fd, STDIN_FILENO) == -1)
			handle_error(strerror(errno), errno, NULL);
		close(file_fd);
		if (dup2(fd[0][1], STDOUT_FILENO) == -1)
			handle_error(strerror(errno), errno, *fd);
		close(fd[0][1]);
	}
	else
	{
		if (dup2(fd[0][1], STDOUT_FILENO) == -1)
			handle_error(strerror(errno), errno, *fd);
		write(STDOUT_FILENO, "", 0);
		close(fd[0][1]);
		list_free(data);
		exit (EXIT_SUCCESS);
	}
}

static void	exe_cmd_child(char **cmds, char **envp, char **argv, t_list *data)
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
		execute_child(cmds, envp, data);
	}
	if (errno != ENOENT)
	{
		list_free(data);
		ptr_free(cmds);
		handle_error(strerror(errno), errno, NULL);
	}
	execute_child(cmds, envp, data);
}

void	first_child(char **argv, char **envp, t_list *data)
{
	char	**commands;

	close_child_fds(data->fd, data->nb_pipes, argv[1]);
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		setup_here_doc(argv[2], data->fd);
		commands = get_commands(argv[3]);
	}
	else
	{	
		setup_fd_child(argv[1], data->fd, data);
		commands = get_commands(argv[2]);
	}
	exe_cmd_child(commands, envp, argv, data);
}
