/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:14:41 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/14 17:28:38 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../header/bonus/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		return (1);
	parsing(argc, argv);
	run_process(argc, argv, envp);
}
