#include "philo.h"

/*Modules wrapping basic functions and the necessary control mesures*/
void    *safe_malloc(size_t bytes)
{
    void    *p;

    p = malloc(bytes);
    if (!p)
        error_exit("Memory allocation failed.", NULL);
    return (p);
}

static void    mutex_error_handling(int value_returned, t_opconst operation, t_simulation *simulation)
{
    if ((value_returned == EINVAL || value_returned == ENOMEM) && operation == INIT)
        error_exit("Mutex initiation failed.", simulation);
    else if ((value_returned == EINVAL || value_returned == EDEADLK) && operation == LOCK)
        error_exit("Mutex lock failed", simulation);
    else if (value_returned == ENOMEM)
        error_exit("The process cannot allocate enough memory to create another mutex.", simulation);
    else if ((value_returned == EDEADLK || value_returned == EPERM) && operation == UNLOCK)
        error_exit("Mutex unlock failed.", simulation);
    else if ((value_returned == EBUSY || value_returned == EINVAL) && operation == DESTROY)
        error_exit("Mutex destroy failed.", simulation);
    else if (value_returned == 0)
        return ;
}

void    safe_mutex(pthread_mutex_t *mutex, t_opconst operation, t_simulation *simulation)
{
    if (operation == INIT)
        mutex_error_handling(pthread_mutex_init(mutex, NULL), INIT, simulation);
    else if (operation == LOCK)
        mutex_error_handling(pthread_mutex_lock(mutex), LOCK, simulation);
    else if (operation == UNLOCK)
        mutex_error_handling(pthread_mutex_unlock(mutex), UNLOCK, simulation);
    else if (operation == DESTROY)
        mutex_error_handling(pthread_mutex_destroy(mutex), DESTROY, simulation);
    else
        error_exit("Wrong operation on mutex.", simulation); //why we should handle this error?
}

static void thread_error_handling(int value_returned, t_opconst operation, t_simulation *simulation)
{
    if ((value_returned == EINVAL || value_returned == EPERM || value_returned == EAGAIN) && operation == CREATE)
        error_exit("Thread creation failed.", simulation);
    else if ((value_returned == EINVAL || value_returned == ESRCH || value_returned == EDEADLK) && operation == JOIN)
        error_exit("Thread join failed.", simulation);
    else if ((value_returned == EINVAL || value_returned == ESRCH) && operation == DETACH)
        error_exit("Thread detach failed.", simulation);
    else if (value_returned == 0)
        return ;
}

void    safe_thread(pthread_t *thread, void *(* routine)(void *), void *data, t_opconst operation)
{
    if (operation == CREATE)
        thread_error_handling(pthread_create(thread, NULL, routine, data), CREATE, (t_simulation *)data);
    else if (operation == JOIN)
        thread_error_handling(pthread_join(*thread, NULL), JOIN, (t_simulation *)data);
    else if (operation == DETACH)
        thread_error_handling(pthread_detach(*thread), DETACH, (t_simulation *)data);
    else
        error_exit("Wrong operation on thread.", (t_simulation *)data);
}