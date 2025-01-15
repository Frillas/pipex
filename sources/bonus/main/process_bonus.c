/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/15 16:02:12 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/bonus/pipex_bonus.h"

void	create_data(int tot_pipes, int tot_cmds, t_list *data)
{
	int	i;

	i = 0;
	data->nb_pipes = tot_pipes;
	data->nb_cmds = tot_cmds;
	data->pid = malloc(sizeof(int) * data->nb_cmds);
	if (!data->pid)
		handle_error("Data_pid: Memory allocation failed", 1, NULL);
	data->fd = malloc(sizeof(int *) * (data->nb_pipes));
	if (!data->fd)
	{
		free(data->pid);
		handle_error("Data_fd: Memory allocation failed", 1, NULL);
	}
	while (i < data->nb_pipes)
	{
		data->fd[i] = malloc(sizeof(int) * 2);
		if (!data->fd[i])
		{
			close_all_fds(data);
			list_free(data);
			handle_error("Data_fd[i]: Memory allocation failed", 1, NULL);
		}
		if (pipe(data->fd[i]) == -1)
		{
			close_all_fds(data);
			list_free(data);
			handle_error("Pipe data->fd error", 1, NULL);
		}
		i++;
	}
}

int	wait_pid(int *pid, int nb_cmds)
{
	int	i;
	int	status;

	i = 0;
	while (i < nb_cmds)
	{
		if (waitpid(pid[i], &status, 0) == -1)
			handle_error(strerror(errno), errno, NULL);
		i++;
	}
	free(pid);
	return ((status >> 8) & 0xFF);
}

void	run_process(int argc, char **argv, char **envp)
{
	t_list	data;
	int		i;
	int		error_status;

	i = 0;
	create_data((argc - 4), (argc - 3), &data);
	while (i < data.nb_cmds)
	{
		data.pid[i] = fork();
		if (data.pid[i] < 0)
		{
			close_all_fds(&data);
			list_free(&data);
			handle_error("Fork error", 1, NULL);
		}
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
	close_all_fds(&data);
	error_status = wait_pid(data.pid, data.nb_cmds);
	exit(error_status);
}
