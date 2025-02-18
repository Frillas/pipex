/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:11:38 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/17 11:26:15 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	execve_fail(char **commands, char **unix_path, char *is_path)
{
	if (is_path == NULL)
	{
		write(STDERR_FILENO, commands[0], ft_strlen(commands[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, "command not found", 18);
	}
	write(2, "\n", 1);
	ptr_free(commands);
	ptr_free(unix_path);
}

void	handle_error(char *message, int error_save, int *fd)
{
	if (fd != NULL)
	{
		if (fd[0] > 0)
			close(fd[0]);
		if (fd[1] > 0)
			close(fd[1]);
	}
	write(STDERR_FILENO, message, ft_strlen(message) + 1);
	write(STDERR_FILENO, "\n", 1);
	exit(error_save);
}

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
			write(STDERR_FILENO, "Error: No valid arguments provided\n", 35);
			return (TRUE);
		}
		i++;
		only_space = TRUE;
	}
	return (FALSE);
}

void	write_command(char *cmds)
{
	write(2, cmds, ft_strlen(cmds) + 1);
	write(2, ": ", 2);
}
