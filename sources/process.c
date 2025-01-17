/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/17 11:34:54 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static void	setup_fd(char *file, int *fd)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (file_fd == -1)
	{
		write(2, file, ft_strlen(file));
		write(2, ": ", 2);
		handle_error(strerror(errno), 1, fd);
	}
	close(fd[1]);
	if (dup2(file_fd, STDOUT_FILENO) == -1)
	{
		close(file_fd);
		handle_error(strerror(errno), errno, fd);
	}
	close(file_fd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		handle_error(strerror(errno), errno, fd);
	close(fd[0]);
}

static void	execute_second_child(char **commands, char **envp)
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
				write_command(commands[0]);
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

static void	handle_second_child(char **argv, char **envp, int *fd)
{
	char	**cmds;

	setup_fd(argv[4], fd);
	cmds = get_commands(argv[3]);
	if (!(access(cmds[0], X_OK)) || !(access(argv[3], X_OK)))
	{
		if (is_file(cmds) == TRUE)
		{
			if (execve(cmds[0], cmds, envp) == -1)
			{
				write_command(cmds[0]);
				ptr_free(cmds);
				handle_error(strerror(errno), errno, NULL);
			}
		}
		execute_second_child(cmds, envp);
	}
	if (errno != ENOENT)
	{
		write_command(cmds[0]);
		ptr_free(cmds);
		handle_error(strerror(errno), 126, NULL);
	}
	execute_second_child(cmds, envp);
}

void	run_process(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	if (pipe(fd) == -1)
		handle_error(strerror(errno), errno, NULL);
	pid1 = fork();
	if (pid1 < 0)
		handle_error(strerror(errno), errno, fd);
	if (pid1 == 0)
		handle_first_child(argv, envp, fd);
	pid2 = fork();
	if (pid2 < 0)
		handle_error(strerror(errno), errno, fd);
	if (pid2 == 0)
		handle_second_child(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	if ((waitpid(pid1, NULL, 0) != pid1))
		handle_error(strerror(errno), errno, NULL);
	if ((waitpid(pid2, &status, 0) != pid2))
		handle_error(strerror(errno), errno, NULL);
	exit((status >> 8) & 0xFF);
}
