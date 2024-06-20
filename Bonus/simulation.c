/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:42:10 by bcai              #+#    #+#             */
/*   Updated: 2024/06/20 12:14:02 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	create_philo_process(t_simulation *simulation)
{
	int		i;
	t_philo	*p;

	p = simulation->philos;
	i = 0;
	while (i < simulation->philo_nbr)
	{
		p[i].pid = safe_fork(simulation);
		if (p[i].pid == 0)
		{
			philo_routine(simulation, &p[i]);
			exit(0);
		}
		i++;
	}
}

static void	*monitor_full(void *data)
{
	t_simulation	*simulation;

	simulation = ((t_philo *)data)->simulation;
	while (1)
	{
		sem_wait(simulation->full);
		simulation->philos_full++;
		if (simulation->philos_full == simulation->philo_nbr)
		{
			sem_post(simulation->endsimul);
			sem_close(simulation->full);
			sem_unlink("full");
			return (NULL);
		}
	}
}

void	start_simulation(t_simulation *simulation)
{
	pthread_t	monitor;

	safe_thread(&monitor, monitor_full, (void *)&(simulation->philos[0]),
		CREATE);
	safe_thread(&monitor, NULL, simulation, DETACH);
	simulation->start_time = get_current_time() * 1e3;
	create_philo_process(simulation);
	sem_wait(simulation->endsimul);
	destroy_all(simulation);
}
