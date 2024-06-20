/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_modules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <bcai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:42:21 by bcai              #+#    #+#             */
/*   Updated: 2024/06/20 12:13:56 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	thread_error_handling(int value_returned, t_opconst operation,
		t_simulation *simulation)
{
	if ((value_returned == EINVAL || value_returned == EPERM
			|| value_returned == EAGAIN) && operation == CREATE)
		error_exit("Thread creation failed.", simulation);
	else if ((value_returned == EINVAL || value_returned == ESRCH
			|| value_returned == EDEADLK) && operation == JOIN)
		error_exit("Thread join failed.", simulation);
	else if ((value_returned == EINVAL || value_returned == ESRCH)
		&& operation == DETACH)
		error_exit("Thread detach failed.", simulation);
	else if (value_returned == 0)
		return ;
}

void	safe_thread(pthread_t *thread, void *(*routine)(void *), void *data,
		t_opconst operation)
{
	if (operation == CREATE)
		thread_error_handling(pthread_create(thread, NULL, routine, data),
			CREATE, ((t_philo *)data)->simulation);
	else if (operation == JOIN)
		thread_error_handling(pthread_join(*thread, NULL), JOIN,
			(t_simulation *)data);
	else if (operation == DETACH)
		thread_error_handling(pthread_detach(*thread), DETACH,
			(t_simulation *)data);
}

void	*safe_malloc(size_t bytes)
{
	void	*p;

	p = malloc(bytes);
	if (!p)
		error_exit("Memory allocation failed.", NULL);
	return (p);
}

pid_t	safe_fork(t_simulation *simulation)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("Fork failed", simulation);
	return (pid);
}
