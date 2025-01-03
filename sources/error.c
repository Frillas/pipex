/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:11:38 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/03 18:16:06 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	execve_fail(char **commands, char **unix_path, char *is_path)
{
	if (is_path == NULL)
	{
		write(2, commands[0], ft_strlen(commands[0]));
		write(2, ": ", 2);
		write(2, "command not found", 18);
	}
	write(2, "\n", 2);
	ptr_free(commands);
	ptr_free(unix_path);
}

void	handle_error(char *message)
{
	write(2, message, ft_strlen(message) + 1);
	exit(EXIT_FAILURE);
}
