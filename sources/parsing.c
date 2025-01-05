/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:58:26 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/05 11:06:20 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	parsing(int argc, char **argv)
{
	if (argc < 5)
		handle_error("Error: Insufficient number of arguments.", 1);
	else if (argc > 5)
		handle_error("Error: Too much arguments.", 1);
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
