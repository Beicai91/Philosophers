/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:06:52 by bcai              #+#    #+#             */
/*   Updated: 2024/06/20 13:08:47 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>  //INT_MAX
# include <pthread.h> //thread ops: create, join, detach; mutex ops: init, lock,
# include <stdbool.h>
# include <stdio.h> //printf
# include <stdlib.h> //malloc free
# include <sys/time.h> //gettimeofday
# include <unistd.h> //usleep

// ANSI escape sequences for formatting printed content
# define RST "\033[0m" /*reset to default color*/
# define R "\033[1;31m" /*bold red*/
# define G "\033[1;32m" /*bold green*/
# define Y "\033[1;33m" /*bold yellow*/
# define B "\033[1;34m" /*bold blue*/
# define M "\033[1;35m" /*bold magenta*/
# define C "\033[1;36m" /*bold cyan*/
# define W "\033[1;37m" /*bold white*/

	// enumeration of mutex and thread functions
	typedef enum opconst {
		INIT,
		LOCK,
		UNLOCK,
		DESTROY,
		CREATE,
		JOIN,
		DETACH
	} t_opconst;

/*structures*/
typedef struct s_philo
{
	int					philo_id;
	long				meals_eaten;
	long				meal_time;
	bool				dead;
	struct s_fork		*left_fork;
	struct s_fork		*right_fork;
	pthread_t			thread;
	struct s_simulation	*simulation;
}						t_philo;

typedef struct s_fork
{
	int					fork_id;
	pthread_mutex_t		fork;
}						t_fork;

typedef struct s_simulation
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				max_meal;
	long				start_time;
	bool				end_simulation;
	pthread_mutex_t		mealtime_lock;
	pthread_mutex_t		mealnum_lock;
	pthread_mutex_t		endsimul_lock;
	t_fork				*forks;
	t_philo				*philos;
}						t_simulation;

// preparation
void					check_args_and_fill(t_simulation *simulation,
							char **argv);
void					data_init(t_simulation *simulation);

// safe modules
void					*safe_malloc(size_t bytes);
void					safe_mutex(pthread_mutex_t *mutex, t_opconst operation,
							t_simulation *simulation);
void					safe_thread(pthread_t *thread, void *(*routine)(void *),
							void *data, t_opconst operation);

// monitor
void					*monitor_routine(void *simulation);

// philos
void					*philo_routine(void *philo);

// utils
long					get_current_time(void);
void					precise_usleep(long sleep_time);
void					print_message(char *str, t_philo *philo);
void					error_exit(char *error_msg, t_simulation *simulation);
void					free_all(t_simulation *simulation);

// execute
void					start_simulation(t_simulation *simulation);

#endif