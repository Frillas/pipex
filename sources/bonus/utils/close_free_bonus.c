/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:41:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/16 09:04:32 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/bonus/pipex_bonus.h"

void	list_free(t_list *data)
{
	int	i;

	i = 0;
	if (data->fd != NULL)
	{
		while ((i < data->nb_pipes) && (data->fd != NULL))
		{
			free(data->fd[i]);
			i++;
		}
		free(data->fd);
	}
	free(data->pid);
}

void	data_free(int *fd[2], char *str, char *limiter, t_list *data)
{
	close(fd[0][0]);
	close(fd[0][1]);
	if (str != NULL)
		free(str);
	if (limiter != NULL)
		free(limiter);
	list_free(data);
}

void	close_all_fds(t_list *data)
{
	int	i;

	i = 0;
	while ((i < data->nb_pipes) && (data->fd[i] != NULL))
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		free(data->fd[i]);
		data->fd[i] = NULL;
		i++;
	}
	free(data->fd);
	data->fd = NULL;
}

void	fd_error(char *str_error, int *fd[2], t_list *data, int file_fd)
{
	if (file_fd == -1)
		close(file_fd);
	if (fd != NULL)
		close_all_fds(data);
	list_free(data);
	handle_error(str_error, EXIT_FAILURE, NULL);
}
