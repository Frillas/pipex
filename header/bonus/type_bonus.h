/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:31:46 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/12 11:04:50 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_BONUS_H
# define TYPE_BONUS_H

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
