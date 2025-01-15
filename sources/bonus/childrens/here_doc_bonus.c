/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:50:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/15 10:01:07 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/bonus/pipex_bonus.h"

static char	*get_str(char *limiter, t_list *data, int *fd[2])
{
	char	*str;
	char	*new;

	str = NULL;
	new = NULL;
	while (1)
	{
		str = get_next_line(0);
		if (str == NULL)
		{
			data_free(fd, str, limiter, data);
			handle_error("Here doc : get next line error", 1, NULL);
		}
		if ((ft_strncmp(limiter, str, ft_strlen(limiter) + 1)) == 0)
			break ;
		new = ft_strjoin(new, str, ft_strlen(new), ft_strlen(str));
		if (new == NULL)
		{
			data_free(fd, str, limiter, data);
			handle_error("Here doc : memory allocation failed", 1, NULL);
		}
		free(str);
	}
	free(str);
	return (new);
}

static char	*add_line_return(char *source, t_list *data, int *fd[2])
{
	char	*limiter;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(source);
	limiter = (char *)malloc(sizeof(char) * size + 2);
	if (limiter == NULL)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		list_free(data);
		handle_error("Here doc : memory allocation failed", 1, NULL);
	}
	while (i < size)
	{
		limiter[i] = source[i];
		i++;
	}
	limiter[i] = '\n';
	limiter[i + 1] = '\0';
	return (limiter);
}

void	setup_here_doc(char *source, int *fd[2], t_list *data)
{
	char	*str;
	char	*limiter;

	limiter = add_line_return(source, data, fd);
	str = get_str(limiter, data, fd);
	if (str == NULL)
	{
		data_free(fd, str, limiter, data);
		handle_error("Here doc : get str error", 1, NULL);
	}
	if (write(fd[0][1], str, ft_strlen(str)) == -1)
	{
		data_free(fd, str, limiter, data);
		handle_error(strerror(errno), errno, NULL);
	}
	if ((dup2(fd[0][0], STDIN_FILENO) == -1) ||
		(dup2(fd[0][1], STDOUT_FILENO) == -1))
	{
		data_free(fd, str, limiter, data);
		handle_error("Here_doc : dup2 error", 1, NULL);
	}
	data_free(fd, str, limiter, data);
	exit(EXIT_SUCCESS);
}
