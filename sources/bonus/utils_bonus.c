/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:41:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/14 16:06:18 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

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
