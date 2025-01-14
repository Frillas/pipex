/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:50:21 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/14 18:25:42 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/bonus/pipex_bonus.h"

static char	*get_str(char *limiter)
{
	char	*str;
	char	*new;

	str = NULL;
	new = NULL;
	while (1)
	{
		str = get_next_line(0);
		if (str == NULL)
			exit (130);
		if ((ft_strncmp(limiter, str, ft_strlen(limiter) + 1)) == 0)
			break ;
		new = ft_strjoin(new, str, ft_strlen(new), ft_strlen(str));
		if (new == NULL)
		{
			free(str);
			handle_error("Memory allocation failed", 1, NULL);
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
		handle_error("Memory allocation failed", 1, NULL);
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
	str = get_str(limiter);
	if (str == NULL)
		handle_error("Here doc : Empty line", 1, NULL);
	if (write(fd[0][1], str, ft_strlen(str)) == -1)
		handle_error(strerror(errno), errno, NULL);
	if (dup2(fd[0][0], STDIN_FILENO) == -1)
		handle_error(strerror(errno), errno, NULL);
	close(fd[0][0]);
	if (dup2(fd[0][1], STDOUT_FILENO) == -1)
		handle_error(strerror(errno), errno, NULL);
	close(fd[0][1]);
	free(limiter);
	exit(EXIT_SUCCESS);
}
