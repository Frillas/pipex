/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/12 08:42:08 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

void	create_data(int tot_pipes, int tot_cmds,t_list *data)
{
	int	i;

	i = 0;
	data->nb_pipes = tot_pipes;
	data->nb_cmds = tot_cmds;
	data->pid = malloc(sizeof(int) * data->nb_cmds);
	if (!data->pid)
		handle_error(strerror(errno), errno, NULL);
	data->fd = malloc(sizeof(int *) * (data->nb_pipes));
	if (!data->fd)
		handle_error(strerror(errno), errno, NULL);
	while (i < data->nb_pipes)
	{
		data->fd[i] = malloc(sizeof(int) * 2);
		if (!data->fd[i])
			handle_error(strerror(errno), errno, NULL);
		if (pipe(data->fd[i]) == -1)
			handle_error(strerror(errno), errno, NULL);
		i++;
	}
}

void	close_all_fds(int *fd[2], int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	run_process(int argc, char **argv, char **envp)
{
	t_list	data;
	int		i;
	int		status;

	i = 0;
	create_data((argc - 4), (argc - 3), &data);
	while (i < data.nb_cmds)
	{
		data.pid[i] = fork();
		if (data.pid[i] < 0)
			handle_error(strerror(errno), errno, NULL);
		else if (data.pid[i] == 0)
		{
			if (i == 0)
				first_child(argv, envp, &data);
			else if (i == data.nb_pipes)
				last_child(argc, argv, envp, &data);
			else
				middle_child(argv, envp, &data, i);
		}
		i++;
	}
	i = 0;
	close_all_fds(data.fd, data.nb_pipes);
	while (i < data.nb_pipes)
	{
		waitpid(data.pid[i], &status, 0);
		i++;
	}
	free(data.pid);
	if (status)
		exit((status >> 8) & 0xFF);
	exit (0);
}
