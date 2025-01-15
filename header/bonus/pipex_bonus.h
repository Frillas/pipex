/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:00:09 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/15 09:02:18 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include "type_bonus.h"

//process_bonus
void	run_process(int argc, char **argv, char **envp);
//first_child
void	first_child(char **argv, char **envp, t_list *data);
//last_child
void	last_child(int argc, char **argv, char **envp, t_list *data);
//middle_child
void	middle_child(char **argv, char **envp, t_list *data, int i);
//parsing
void	parsing(int argc, char **argv);
//utils
size_t	ft_strlen(const char *s);
void	ptr_free(char **args);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
//utils_bonus
void	list_free(t_list *data);
void	data_free(int *fd[2], char *str, char *limiter, t_list *data);
//ft_split
char	**ft_split(char const *s, char c);
//arg_split
char	**arg_split(char const *s);
//path  
char	**get_unix_path(char **envp, char **commands);
char	**get_commands(char *src);
char	*get_path(char *unix_path, char *commands, char **unix_p, char **cmd);
t_bool	is_file(char **cmds);
//error.c
void	execve_fail(char **commands, char **unix_path, char *is_path);
void	handle_error(char *message, int error_save, int *fd);
t_bool	is_empty(int argc, char **argv);
//here_doc.c
void	setup_here_doc(char *limiter, int *fd[2], t_list *data);
//get_next_line
char	*get_next_line(int fd);
char	*check_buf_size(int fd, char *remaining);
char	*ft_big_buf(int fd, char *buffer, char *rem);
char	*ft_add_remain(char *remain);
char	*ft_add_line(char *rem);
//get_next_line_utils
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char const *s2, size_t k, size_t l);
void	ft_copy(size_t size, char *new_rem, char *end);
char	*ft_small_buf(int fd, char *rem, int nb);
#endif
