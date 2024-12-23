/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:45:58 by aroullea          #+#    #+#             */
/*   Updated: 2024/12/23 16:21:20 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	commands(char **argv, char **envp)
{
	char	**args;
	char	**mypath;
	char	*full_path;
	int		i;
	char	*env_path;

	i = 0;
	while (envp && *envp)
	{
		if(!strncmp("PATH", *envp, 4))
		{
			env_path = *envp + 5;
			mypath = ft_split(env_path, ':');
			if (mypath == NULL)
				exit (EXIT_FAILURE);
		}
		envp++;
	}
	args = ft_split(argv[2], ' ');
	if (args == NULL)
		exit (EXIT_FAILURE);
	while(mypath[i])
	{
		full_path = (char *) malloc(ft_strlen(mypath[i]) + ft_strlen(args[0]) + 2);
		ft_strlcpy(full_path, mypath[i], ft_strlen(mypath[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(mypath[i]) + 2);
		ft_strlcat(full_path, args[0], (ft_strlen(mypath[i]) + ft_strlen(args[0]) + 2));
		i++;
		if (access(argv[1], F_OK | W_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				if (execve(full_path, args, envp) == -1)
					write(1, strerror(errno), ft_strlen(strerror(errno)));
				free(full_path);
				break ;
			}
		}
		free(full_path);
		i++;
	}
	write(1, "\n", 1);
	ptr_free(args);
}
