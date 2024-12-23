/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:58:26 by aroullea          #+#    #+#             */
/*   Updated: 2024/12/22 17:49:29 by aroullea         ###   ########.fr       */
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
}
