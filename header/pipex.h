/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:58:26 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/03 13:18:06 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "type.h"

// parsing
void	parsing(int argc, char **argv);
//utils
t_bool	is_empty(int argc, char **argv);
size_t	ft_strlen(const char *s);
void	ptr_free(char **args);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
//utils2
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	handle_error(char *message);
//ft_split
char	**ft_split(char const *s, char c);
//commands
void	execute_child(char **argv, char **envp);
void	execve_fail(char **commands, char **unix_path, char *is_path);
void    handle_child(char **argv, char **envp, int *fd);
void	run_process(char **argv, char **envp);
//path
char	**get_unix_path(char **envp);
char	**get_commands(char *src, char **unix_path);
char	*get_path(char *unix_path, char *commands, char **unix_p, char **cmd);

#endif
