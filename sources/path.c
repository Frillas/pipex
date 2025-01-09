/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:44:50 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/08 11:52:00 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	**get_unix_path(char **envp, char **commands)
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
			{
				ptr_free(commands);
				exit (EXIT_FAILURE);
			}
			break ;
		}
		envp++;
	}
	return (mypath);
}

char	**get_commands(char *src)
{
	char	**args;

	args = arg_split(src);
	if (args == NULL)
		exit (EXIT_FAILURE);
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

t_bool	is_file(char **cmds)
{
	char	*path;
	size_t	len_cmd;

	if (cmds[0][0] == '/' || (cmds[0][0] == '.' && cmds[0][1] == '/'))
		return (TRUE);
	else
	{
		len_cmd = ft_strlen(cmds[0]);
		while (len_cmd > 0)
		{
			if (cmds[0][len_cmd] == '/')
				break ;
			len_cmd--;
		}
		if (len_cmd == 0)
			return (FALSE);
		if (is_dir(cmds, len_cmd) == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

t_bool	is_dir(char **cmds, size_t len_cmd)
{
	char	*path;
	size_t	i;

	i = 0;
	path = (char *) malloc(sizeof(char) * (len_cmd + 1));
	if (path == NULL)
		return (FALSE);
	while (i < len_cmd)
	{
		path[i] = cmds[0][i];
		i++;
	}
	path[i] = '\0';
	if (access(path, X_OK) == 0)
		return (TRUE);
	free(path);
	return (FALSE);
}
