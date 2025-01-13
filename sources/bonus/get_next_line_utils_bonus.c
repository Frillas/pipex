/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:23:49 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/13 18:12:48 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char const *s2, size_t k, size_t l)
{
	size_t	i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (k + l + 1));
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (i < k)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < k + l)
	{
		str[i] = s2[i - k];
		i++;
	}
	str[k + l] = '\0';
	free(s1);
	return (str);
}

void	ft_copy(size_t size, char *new_rem, char *end)
{
	size_t	i;

	i = 1;
	while ((i <= size) && (end[i] != '\0'))
	{
		new_rem[i - 1] = end[i];
		i++;
	}
	new_rem[i - 1] = '\0';
}

char	*ft_small_buf(int fd, char *rem, int nb)
{
	char	*end;
	int		tot;
	char	buffer[1024 + 1];

	end = NULL;
	tot = 0;
	while ((end == NULL) && (nb > 0))
	{
		nb = read(fd, buffer + tot, BUFFER_SIZE);
		if (nb == -1)
		{
			free(rem);
			return (NULL);
		}
		tot += nb;
		buffer[tot] = '\0';
		end = ft_strchr(buffer, '\n');
		if ((tot + BUFFER_SIZE > 1024) || ((nb == 0) && (buffer[0])) || (end))
		{
			rem = ft_strjoin(rem, buffer, ft_strlen(rem), ft_strlen(buffer));
			tot = 0;
			buffer[0] = '\0';
		}
	}
	return (rem);
}
