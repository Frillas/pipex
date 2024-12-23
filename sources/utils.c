/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:19 by aroullea          #+#    #+#             */
/*   Updated: 2024/12/22 18:07:14 by aroullea         ###   ########.fr       */
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
