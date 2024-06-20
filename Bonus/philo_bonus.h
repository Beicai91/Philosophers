/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:09:08 by bcai              #+#    #+#             */
/*   Updated: 2024/06/20 12:09:14 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// ANSI escape sequences for formatting printed content
# define RST "\033[0m"  /*reset to default color*/
# define R "\033[1;31m" /*bold red*/
# define G "\033[1;32m" /*bold green*/
# define Y "\033[1;33m" /*bold yellow*/
# define B "\033[1;34m" /*bold blue*/
# define M "\033[1;35m" /*bold magenta*/
# define C "\033[1;36m" /*bold cyan*/
# define W "\033[1;37m" /*bold white*/

// enumeration of mutex and thread functions
typedef enum opconst
{
	CREATE,
	JOIN,
	DETACH
}						t_opconst;

typedef struct s_philo
{
	pid_t				pid;
	int					philo_id;
	long				meals_eaten;
	long				meal_time;
	struct s_simulation	*simulation;
}						t_philo;

typedef struct s_simulation
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				max_meal;
	long				start_time;
	long				philos_full;
	sem_t				*forks;
	sem_t				*death_check;
	sem_t				*endsimul;
	sem_t				*full;
	struct s_philo		*philos;
}						t_simulation;

void					check_args_and_fill(t_simulation *simulation,
							char **argv);
void					data_init(t_simulation *simulation);
void					start_simulation(t_simulation *simulation);
void					philo_routine(t_simulation *simulation, t_philo *philo);

// safe modules
void					safe_thread(pthread_t *thread, void *(*orutine)(void *),
							void *data, t_opconst operation);
void					*safe_malloc(size_t bytes);
pid_t					safe_fork(t_simulation *simulation);

// utils
long					get_current_time(void);
void					print_message(char *str, t_philo *philo);
void					error_exit(char *error_msg, t_simulation *simulation);
void					destroy_all(t_simulation *simulation);
void					precise_usleep(long sleep_time);

#endif