/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/12 11:37:01 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

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

int	setup_fd_parent(char *file, int *fd)
{
	int	file_fd;

	file_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (file_fd == -1)
		handle_error(strerror(errno), 2, fd);
	close(fd[1]);
	if (dup2(file_fd, STDOUT_FILENO) == -1)
		handle_error(strerror(errno), errno, fd);
	close(file_fd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		handle_error(strerror(errno), errno, fd);
	close(fd[0]);
	return (file_fd);
}

void	handle_parent(char **argv, char **envp, int *fd)
{
	char	**cmds;
	int		file_fd;

	file_fd = setup_fd_parent(argv[4], fd);
	cmds = get_commands(argv[3]);
	if (!(access(cmds[0], X_OK)) || !(access(argv[3], X_OK)))
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

void	run_process(char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		exit_code;

	if (pipe(fd) == -1)
		handle_error(strerror(errno), errno, NULL);
	pid1 = fork();
	if (pid1 < 0)
		handle_error(strerror(errno), errno, NULL);
	if (pid1 == 0)
		handle_child(argv, envp, fd);
	pid2 = fork();
	if (pid2 < 0)
		handle_error(strerror(errno), errno, NULL);
	if (pid2 == 0)
		handle_parent(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	if ((waitpid(pid1, NULL, 0) != pid1))
		handle_error(strerror(errno), errno, NULL);
	if ((waitpid(pid2, &status, 0) != pid2))
		handle_error(strerror(errno), errno, NULL);
	exit(exit_code = (status >> 8) & 0xFF);
}
