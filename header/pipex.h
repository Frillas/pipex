/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:58:26 by aroullea          #+#    #+#             */
/*   Updated: 2024/12/22 18:07:29 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "type.h"

// parsing
void    parsing(int argc, char **argv);
//utils
t_bool  is_empty(int argc, char **argv);
size_t  ft_strlen(const char *s);
void    ptr_free(char **args);
//ft_split
char    **ft_split(char const *s, char c);
//commands
void    commands(char **argv);

#endif
