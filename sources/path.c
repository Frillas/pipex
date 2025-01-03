/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:44:50 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/03 11:50:21 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	**get_unix_path(char **envp)
{
	char	**mypath;
	char	*env_path;

	while (envp && *envp)
	{
		if (!strncmp("PATH", *envp, 4))
		{
			env_path = *envp + 5;
			mypath = ft_split(env_path, ':');
			if (mypath == NULL)
				exit (EXIT_FAILURE);
			break ;
		}
		envp++;
	}
	return (mypath);
}

char	**get_commands(char *src, char **unix_path)
{
	char	**args;

	args = ft_split(src, ' ');
	if (args == NULL)
	{
		ptr_free(unix_path);
		exit (EXIT_FAILURE);
	}
	return (args);
}

char	*get_path(char *unix_path, char *commands, char **unix_p, char **cmd)
{
	char	*path;
	size_t	len_path;
	size_t	len_cmd;

	len_path = ft_strlen(unix_path);
	len_cmd = ft_strlen(commands);
	path = (char *) malloc(len_path + len_cmd + 2);
	if (path == NULL)
	{
		ptr_free(unix_p);
		ptr_free(cmd);
		exit (EXIT_FAILURE);
	}
	ft_strlcpy(path, unix_path, len_path + 1);
	ft_strlcat(path, "/", len_path + 2);
	ft_strlcat(path, commands, (len_path + len_cmd + 2));
	return (path);
}
