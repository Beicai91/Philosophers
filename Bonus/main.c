/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:41:28 by bcai              #+#    #+#             */
/*   Updated: 2024/06/20 12:13:21 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_simulation	simulation;

	if (argc == 5 || argc == 6)
	{
		check_args_and_fill(&simulation, argv);
		data_init(&simulation);
		start_simulation(&simulation);
	}
	else
		error_exit("Pass the right amount of arguments.", NULL);
}
