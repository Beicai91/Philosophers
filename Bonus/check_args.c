/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:41:38 by bcai              #+#    #+#             */
/*   Updated: 2024/06/20 12:09:28 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	get_start_index(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
		error_exit("Invalid arguments: you probably entered a negative number",
			NULL);
	else if (str[i] == '+')
		i++;
	if (is_digit(str[i]))
	{
		while (is_digit(str[i]))
		{
			len++;
			i++;
		}
	}
	else
		error_exit("Invalid arguments.", NULL);
	if (len > 10)
		error_exit("Argument too big.", NULL);
	return (i - len);
}

static long	ft_atol(char *str)
{
	long	num;
	int		start_index;

	start_index = get_start_index(str);
	num = 0;
	while (is_digit(str[start_index]))
		num = num * 10 + (str[start_index++] - 48);
	if (num > INT_MAX)
		error_exit("Argument too big.", NULL);
	return (num);
}

void	check_args_and_fill(t_simulation *simulation, char **argv)
{
	simulation->philo_nbr = ft_atol(argv[1]);
	if (simulation->philo_nbr > 200)
		error_exit("Philosophers can't be more than 200.", NULL);
	simulation->time_to_die = ft_atol(argv[2]) * 1000;
	simulation->time_to_eat = ft_atol(argv[3]) * 1000;
	simulation->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (simulation->time_to_die < 60000 || simulation->time_to_eat < 60000
		|| simulation->time_to_sleep < 60000)
		error_exit("Time shouldn't be less than 60ms.", NULL);
	if (argv[5])
		simulation->max_meal = ft_atol(argv[5]);
	else
		simulation->max_meal = -1;
}
