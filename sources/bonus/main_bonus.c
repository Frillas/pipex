/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <aroullea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:14:41 by aroullea          #+#    #+#             */
/*   Updated: 2025/01/11 11:43:12 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/bonus/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	int	nb_pipe;
	int	nb_fd;

	nb_pipe = argc - 3;
	nb_fd = argc -4;
	parsing(argc, argv);
	run_process(argv, envp, nb_pipe, nb_fd);
}
