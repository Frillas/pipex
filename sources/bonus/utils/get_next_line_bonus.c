/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:23:55 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/14 17:07:07 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/bonus/pipex_bonus.h"

char	*ft_add_line(char *rem)
{
	char	*new;
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (rem[size] && rem[size] != '\n')
		size++;
	new = (char *) malloc(sizeof(char) * (size + 1 + (rem[size] == '\n')));
	if (new == NULL)
		return (NULL);
	while (i < size + (rem[size] == '\n'))
	{
		new[i] = rem[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_add_remain(char *remain)
{
	char	*new_rem;
	char	*end;
	size_t	size;

	end = ft_strchr(remain, '\n');
	if (end)
		size = ft_strlen(end + 1);
	if (end && size)
	{
		new_rem = (char *) malloc(sizeof(char) * (size + 1));
		if (new_rem == NULL)
		{
			free(remain);
			return (NULL);
		}
		ft_copy(size, new_rem, end);
		free(remain);
	}
	else
	{
		free (remain);
		return (NULL);
	}
	return (new_rem);
}

char	*ft_big_buf(int fd, char *buffer, char *rem)
{
	char	*end;
	int		nb_read;

	end = NULL;
	nb_read = 1;
	while (end == NULL)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(rem);
			free(buffer);
			return (NULL);
		}
		buffer[nb_read] = '\0';
		if (nb_read == 0)
			break ;
		rem = ft_strjoin(rem, buffer, ft_strlen(rem), ft_strlen(buffer));
		if (rem == NULL)
			break ;
		end = ft_strchr(buffer, '\n');
	}
	free(buffer);
	return (rem);
}

char	*check_buf_size(int fd, char *remaining)
{
	char	*buffer;

	if (BUFFER_SIZE <= 1024)
		remaining = ft_small_buf(fd, remaining, 1);
	else
	{
		buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
		{
			free(remaining);
			return (NULL);
		}
		remaining = ft_big_buf(fd, buffer, remaining);
	}
	return (remaining);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*remain;

	line = NULL;
	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	remain = check_buf_size(fd, remain);
	if (remain == NULL)
		return (NULL);
	line = ft_add_line(remain);
	if (line == NULL)
	{
		free(remain);
		remain = NULL;
		return (NULL);
	}
	remain = ft_add_remain(remain);
	return (line);
}
