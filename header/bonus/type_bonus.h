/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:31:46 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/13 18:13:37 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_BONUS_H
# define TYPE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_list
{
	int		**fd;
	pid_t	*pid;
	int		nb_pipes;
	int		nb_cmds;
}	t_list;

#endif
