/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:40:47 by bcai              #+#    #+#             */
/*   Updated: 2024/06/20 12:08:15 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;
	long			time;

	if (gettimeofday(&tv, NULL) == -1)
		error_exit("Get_time_of_day operation failed.", NULL);
	time = tv.tv_sec * 1e3 + tv.tv_usec / 1e3;
	return (time);
}

void	precise_usleep(long sleep_time)
{
	long	start;
	long	current;
	long	time_passed;
	long	remaining;

	start = get_current_time() * 1e3;
	time_passed = 0;
	while (time_passed < sleep_time)
	{
		current = get_current_time() * 1e3;
		time_passed = current - start;
		remaining = sleep_time - time_passed;
		if (remaining > 1000)
			usleep(remaining / 2);
	}
}

void	print_message(char *str, t_philo *philo)
{
	long	time;

	time = get_current_time() * 1000 - philo->simulation->start_time;
	printf("After %ld millisecond, philo N.%d %s\n", time / 1000,
		philo->philo_id, str);
}

void	error_exit(char *error_msg, t_simulation *simulation)
{
	printf("%s\n", error_msg);
	if (simulation != NULL)
	{
		if (simulation->philos && simulation->forks)
			free_all(simulation);
	}
	exit(EXIT_FAILURE);
}

void	free_all(t_simulation *simulation)
{
	free(simulation->philos);
	free(simulation->forks);
}
