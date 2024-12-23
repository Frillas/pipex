/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:19 by aroullea          #+#    #+#             */
/*   Updated: 2024/12/23 15:43:33 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

t_bool	is_empty(int argc, char **argv)
{
	int		i;
	t_bool	only_space;
	char	*arg;

	i = 1;
	only_space = TRUE;
	while (i < argc)
	{
		arg = argv[i];
		while (*arg && only_space)
		{
			if (*arg != ' ')
				only_space = FALSE;
			arg++;
		}
		if (only_space == TRUE)
		{
			write(2, "Error : empty argument\n", 23);
			return (TRUE);
		}
		i++;
		only_space = TRUE;
	}
	return (FALSE);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ptr_free(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{	
		free(args[i]);
		i++;
	}
	free(args);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_dst = 0;
	len_src = 0;
	if (dst != NULL)
		len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size != 0 && (size > len_dst))
	{
		while ((i < size - len_dst - 1) && (src[i] != '\0'))
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[i + len_dst] = '\0';
		return (len_dst + len_src);
	}
	return (len_src + size);
}
