/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:41:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/15 09:24:10 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/bonus/pipex_bonus.h"

void	list_free(t_list *data)
{
	int	i;

	i = 0;
	while (i < data->nb_pipes)
	{
		free(data->fd[i]);
		i++;
	}
	free(data->fd);
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
