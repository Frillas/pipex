/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:58:26 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/14 16:48:14 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include "type.h"

// parsing
void	parsing(int argc, char **argv);
//utils
size_t	ft_strlen(const char *s);
void	ptr_free(char **args);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
//ft_split
char	**ft_split(char const *s, char c);
//arg_split
char	**arg_split(char const *s);
//process
void	run_process(char **argv, char **envp);
//path
char	**get_unix_path(char **envp, char **commands);
char	**get_commands(char *src);
char	*get_path(char *unix_path, char *commands, char **unix_p, char **cmd);
t_bool	is_file(char **cmds);
//error.c
void	execve_fail(char **commands, char **unix_path, char *is_path);
void	handle_error(char *message, int error_save, int *fd);
t_bool	is_empty(int argc, char **argv);
//children.c
void	handle_first_child(char **argv, char **envp, int *fd);

#endif
