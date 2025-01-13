/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:50:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/13 18:15:31 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

static char	*get_str(char *limiter)
{
	char	*str;
	char	*new_line;

	str = NULL;
	while (1)
	{
		str = get_next_line(0);
		if (str == NULL)
		{
			free (str);
			exit (130);
		}
		new_line = ft_strjoin(new_line, str, ft_strlen(new_line), ft_strlen(str));
		if (new_line == NULL)
		{
			free(str);
			handle_error("Memory allocation failed", 1, NULL);
		}
		if ((ft_strncmp(limiter, str, ft_strlen(limiter) + 1)) == 0)
			break ;
	}
	return (new_line);
}

void	setup_here_doc(char *limiter, int *fd[2])
{
	char	*str;

	str = get_str(limiter);
	if (str == NULL)
		handle_error("Here doc : Empty line", 1, NULL);
	write(fd[0][0], str, ft_strlen(str) + 1);
	if (dup2(fd[0][0], STDIN_FILENO) == -1)
		handle_error(strerror(errno), errno, NULL);
	close(fd[0][0]);
	if (dup2(fd[0][1], STDOUT_FILENO) == -1)
		handle_error(strerror(errno), errno, NULL);
	close(fd[0][1]);
}
