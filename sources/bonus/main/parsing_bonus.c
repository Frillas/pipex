/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:58:26 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/14 17:06:47 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/bonus/pipex_bonus.h"

void	parsing(int argc, char **argv)
{
	int	res;

	res = ft_strncmp("here_doc", argv[1], 9);
	if (argc < 5)
		handle_error("Error: Insufficient number of arguments.", 1, NULL);
	if (res == 0)
	{
		argv = argv + 2;
		argc -= 2;
		if (is_empty(argc, argv))
			exit(EXIT_FAILURE);
	}
	else
	{
		if (is_empty(argc, argv))
			exit(EXIT_FAILURE);
		if (access(argv[1], F_OK | R_OK) != 0)
		{
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, argv[1], ft_strlen(argv[1]));
			write(STDERR_FILENO, "\n", 1);
		}
	}
}
