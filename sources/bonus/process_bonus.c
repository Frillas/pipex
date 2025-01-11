/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/11 12:30:00 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

void	run_process(char **argv, char **envp,int nb_pipe, int nb_fd)
{
	int fd[nb_fd][2];
	int	pid[nb_pipe];
	int	i;
	int	j;
	int	status;
	int	exit_code;

	i = 0;
	j = 0;
	while (i < nb_pipe)
	{
		if (pipe(fd[i]) == -1)
			handle_error(strerror(errno), errno, NULL);
		i++;
	}
	i = 0;
	while (i < nb_pipe)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			handle_error(strerror(errno), errno, NULL);
		else if (pid[i] == 0)
		{
			if (i == 0)
				first_child(argv, envp, fd, nb_fd);
			else if (i == nb_fd)
				last_child(argv, envp, fd, nb_fd);
			else
			{
				close_middle_fds(fd, nb_fd, i);
				middle_child(argv, envp, fd, i);
			}
		}
		i++;
	}
	i = 0;
	while (i < nb_fd)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	while (j < nb_fd)
	{
		waitpid(pid[j], &status, 0);
		j++;
	}
	exit(exit_code = (status >> 8) & 0xFF);
}
