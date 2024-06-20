#include "philo.h"

static void    create_philo_threads(t_simulation *simulation)
{
    int i;

    i = -1;
    while (++i < simulation->philo_nbr)
        safe_thread(&(simulation->philos[i].thread), philo_routine, &(simulation->philos[i]), CREATE);
}

static void    join_philo_threads(t_simulation *simulation)
{
    int i;
    t_philo *philos;

    i = -1;
    philos = simulation->philos;
    while (++i < simulation->philo_nbr)
        safe_thread(&(philos[i].thread), NULL, NULL, JOIN);
}

static void    destroy_mutex(t_simulation *simulation)
{
    int i;

    i = -1;
    while (++i < simulation->philo_nbr)
    safe_mutex(&(simulation->forks[i].fork), DESTROY, simulation);
    safe_mutex(&(simulation->endsimul_lock), DESTROY, simulation);
    safe_mutex(&(simulation->mealnum_lock), DESTROY, simulation);
    safe_mutex(&(simulation->mealtime_lock), DESTROY, simulation);
}

void    start_simulation(t_simulation *simulation)
{
    pthread_t   monitor;

    simulation->start_time = get_current_time() * 1000;
    safe_thread(&monitor, monitor_routine, (void *)simulation, CREATE);
    create_philo_threads(simulation);
    safe_thread(&monitor, NULL, NULL, JOIN);
    join_philo_threads(simulation);
    destroy_mutex(simulation);
}