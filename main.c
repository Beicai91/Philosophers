/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:38:14 by bcai              #+#    #+#             */
/*   Updated: 2024/06/20 12:03:44 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (argc == 5 || argc == 6)
	{
		check_args_and_fill(&simulation, argv);
		data_init(&simulation);
		start_simulation(&simulation);
		free_all(&simulation);
	}
	else
		error_exit("Pass the right amount of arguments.", NULL);
}
