/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 12:31:46 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/11 18:03:13 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

typedef struct s_data;
{
	int	**fd;
	int	*pid;
	int	nb_pipes;
} t_data;

#endif
