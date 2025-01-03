/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/03 15:22:02 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	execve_fail(char **commands, char **unix_path, char *is_path)
{
	if (is_path == NULL)
	{
		write(2, commands[0], ft_strlen(commands[0]));
		write(2, ": ", 2);
		write(2, "command not found", 18);
	}
	write(2, "\n", 2);
	ptr_free(commands);
	ptr_free(unix_path);
}

void	execute_child(char **argv, char **envp)
{
	char	**commands;
	char	**unix_path;
	char	*path;
	int		i;
	int		fd;

	i = 0;
	unix_path = get_unix_path(envp);
	commands = get_commands(argv[2], unix_path);
	while (unix_path[i])
	{
		path = get_path(unix_path[i], commands[0], unix_path, commands);
		if (access(path, X_OK) == 0)
		{
			if (execve(path, commands, envp) == -1)
				write(2, strerror(errno), ft_strlen(strerror(errno) + 1));
			free(path);
			break ;
		}
		free(path);
		i++;
	}
	execve_fail(commands, unix_path, unix_path[i]);
	exit (EXIT_FAILURE);
}

void	handle_child(char **argv, char **envp, int *fd)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		handle_error("dup2 error\n");
	}
	close(fd[1]);
	execute_child(argv, envp);
}

void	run_process(char **argv, char **envp)
{
	int		status;
	int		fd[2];
	int		nb_read;
	char	buffer[4096];
	pid_t	pid;

	if (pipe(fd) == -1)
		handle_error("pipe error\n");
	pid = fork();
	if (pid < 0)
		handle_error("fork error\n");
	if (pid == 0)
		handle_child(argv, envp, fd);
	pid = waitpid(pid, &status, 0);
	if (pid < 0)
		handle_error("waitpid error\n");
	if (status)
		exit(EXIT_FAILURE);
	close(fd[1]);
	nb_read = 1;
	while (nb_read > 0)
	{
		nb_read = read(fd[0], buffer, sizeof(buffer) - 1);
		if (nb_read < 0)
			exit(EXIT_FAILURE);
		buffer[nb_read] = '\0';
		write(1, buffer, ft_strlen(buffer) + 1);
	}
	close(fd[0]);
}
