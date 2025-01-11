/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/11 18:48:27 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

void	create_pipe(int nb_cmd, t_data *pipes)
{
	int	i;

	i = 0;
	pipes->nb_pipes = nb_cmd;
	pipes->pid = malloc(sizeof(int) * (nb_cmd + 1));
	if (!pipes->pid)
		handle_error(strerror(errno), errno, NULL);
	pipes->fd = malloc(sizeof(int *) * pipes->nb_pipes)
	if (!pipes->fd)
		handle_error(strerror(errno), errno, NULL);
	while (i < pipes->nb_pipes)
	{
		pipes->fd[i] = malloc(sizeof(int) * 2);
		if (!pipes->fd[i])
			handle_error(strerror(errno), errno, NULL);
		if (pipe(pipes->fd[i]) == -1)
			handle_error(strerror(errno), errno, NULL);
		i++;
	}
}

void	close_all_fds(int fd[][2], int nb_fd)
{
	int	i;

	i = 0;
	while (i < nb_fd)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	run_process(int argc, char **argv, char **envp)
{
	t_data	pipes;
	int		i;
	int		status;

	i = 0;
	create_pipe((argc - 4), &pipes);
	if (pipes == NULL)
		handle_error(strerror(errno), errno, NULL);
	while (i < (argc - 3))
	{
		pid[i] = fork();
		if (pid[i] < 0)
			handle_error(strerror(errno), errno, NULL);
		else if (pid[i] == 0)
		{
			if (i == 0)
				first_child(argv, envp, fd, (argc - 4));
			else if (i == (argc - 4))
				last_child(argc, argv, envp, fd);
			else
			{
				close_middle_fds(fd, (argc - 4), i);
				middle_child(argv, envp, fd, i);
			}
		}
		i++;
	}
	i = 0;
	close_all_fds(fd, (argc - 4));
	while (i < (argc - 3))
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (status)
		exit((status >> 8) & 0xFF);
	exit (0);
}
