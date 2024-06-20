/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:41:55 by bcai              #+#    #+#             */
/*   Updated: 2024/06/20 12:09:23 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	semaphore_init(t_simulation *simulation)
{
	sem_unlink("forks");
	sem_unlink("death_check");
	sem_unlink("endsimul");
	sem_unlink("full");
	simulation->death_check = sem_open("death_check", O_CREAT, 0600, 1);
	simulation->endsimul = sem_open("endsimul", O_CREAT, 0600, 0);
	simulation->full = sem_open("full", O_CREAT, 0600, 0);
	simulation->forks = sem_open("forks", O_CREAT, 0600, simulation->philo_nbr);
}

static void	philo_init(t_simulation *simulation)
{
	int		i;
	t_philo	*p;

	simulation->philos = safe_malloc(sizeof(t_philo) * simulation->philo_nbr);
	p = simulation->philos;
	i = 0;
	while (i < simulation->philo_nbr)
	{
		p[i].pid = -1;
		p[i].philo_id = i + 1;
		p[i].meals_eaten = 0;
		p[i].meal_time = 0;
		p[i].simulation = simulation;
		i++;
	}
}

void	data_init(t_simulation *simulation)
{
	simulation->forks = NULL;
	simulation->death_check = NULL;
	simulation->endsimul = NULL;
	simulation->full = NULL;
	simulation->philos = NULL;
	simulation->philos_full = 0;
	philo_init(simulation);
	semaphore_init(simulation);
}
