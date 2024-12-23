/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2024/12/22 18:55:50 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	commands(char **argv)
{
	char	**args;
	char	*envp[2];

	args = ft_split(argv[2], ' ');
	if (args == NULL)
		exit (EXIT_FAILURE);
	envp[0] = "PATH=/bin:/usr/bin";
	envp[1] = NULL;	
	if (access(argv[1], F_OK | W_OK) == 0)
	{
		if (execve(argv[2], args, envp) == -1)
			write(1, strerror(errno), ft_strlen(strerror(errno)));
	}
	else
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
	ptr_free(args);
}
