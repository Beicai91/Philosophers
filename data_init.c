#include "philo.h"


static void philos_init(t_simulation *simulation)
{
    int i;

    i = -1;
    while (++i < simulation->philo_nbr)
    {
        simulation->philos[i].philo_id = i + 1; //philo_id starts from 1
        simulation->philos[i].dead = false;
        simulation->philos[i].meals_eaten = 0;
        simulation->philos[i].meal_time = 0;
        simulation->philos[i].simulation = simulation;
        if (i == 0)
            simulation->philos[i].right_fork = &(simulation->forks[simulation->philo_nbr - 1]);
        else
            simulation->philos[i].right_fork = &(simulation->forks[i - 1]);
        simulation->philos[i].left_fork = &(simulation->forks[i]);
    }
}

void    data_init(t_simulation *simulation)
{
    int i;

    simulation->philos = NULL;
    simulation->forks = NULL;
    safe_mutex(&(simulation->mealtime_lock), INIT, simulation);
    safe_mutex(&(simulation->mealnum_lock), INIT, simulation);
    safe_mutex(&(simulation->endsimul_lock), INIT, simulation);
    simulation->end_simulation = false;
    simulation->philos = safe_malloc(sizeof(t_philo) * simulation->philo_nbr);
    simulation->forks = safe_malloc(sizeof(t_fork) * simulation->philo_nbr);
    i = -1;
    while (++i < simulation->philo_nbr)
    {
        safe_mutex(&(simulation->forks[i].fork), INIT, simulation);
        simulation->forks[i].fork_id = i;
    }
    philos_init(simulation);
}