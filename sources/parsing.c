/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:58:26 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/03 12:48:08 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	parsing(int argc, char **argv)
{
	if (argc < 3)
	{
		write(2, "Error: Insufficient number of arguments.\n", 41);
		exit (EXIT_FAILURE);
	}
	if (is_empty(argc, argv))
		exit(EXIT_FAILURE);
	if (access(argv[1], F_OK | R_OK) != 0)
	{
		write(1, argv[1], ft_strlen(argv[1]));
		write(1, ": ", 2);
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
		exit(EXIT_FAILURE);
	}
}
