#include "philo.h"

static void    update_philo_status(t_philo *philo)
{
    t_simulation *simulation;

    simulation = philo->simulation;
    safe_mutex(&(simulation->mealtime_lock), LOCK, simulation);
    if ((get_current_time() * 1000 - simulation->start_time) - philo->meal_time > simulation->time_to_die)
    {
        philo->dead = true;
        safe_mutex(&(simulation->mealtime_lock), UNLOCK, simulation);
        safe_mutex(&(simulation->endsimul_lock), LOCK, simulation);
        simulation->end_simulation = true;
        safe_mutex(&(simulation->endsimul_lock), UNLOCK, simulation);
        print_message("died", philo);
        return;
    }
    safe_mutex(&(simulation->mealtime_lock), UNLOCK, simulation);
}

static int check_philo_dead(t_philo *philos)
{
    int i;
    t_simulation    *simulation;
    int dead_flag;

    dead_flag = 0;
    simulation = philos[0].simulation;
    i = -1;
    while (++i < simulation->philo_nbr)
    {
        update_philo_status(&philos[i]);
        if (philos[i].dead == true)
        {
            dead_flag = 1;
            break;
        }
    }
    return (dead_flag);
}

static int    philo_full(t_philo *philos)
{
    int i;
    t_simulation    *simulation;
    int full_philos;
    int allfull_flag;

    allfull_flag = 0;
    simulation = philos[0].simulation;
    full_philos = 0;
    i = -1;
    while (++i < simulation->philo_nbr)
    {
        safe_mutex(&(simulation->mealnum_lock), LOCK, simulation);
        if (philos[i].meals_eaten >= simulation->max_meal && simulation->max_meal != -1)
            full_philos++;
        safe_mutex(&(simulation->mealnum_lock), UNLOCK, simulation);
    }
    if (full_philos == simulation->philo_nbr)
    {
        safe_mutex(&(simulation->endsimul_lock), LOCK, simulation);
        simulation->end_simulation = true;
        safe_mutex(&(simulation->endsimul_lock), UNLOCK, simulation);
        allfull_flag = 1;
    }
    return (allfull_flag);
}

void    *monitor_routine(void *simulation)
{
    t_philo *philos;

    philos = ((t_simulation *)simulation)->philos;
    while (1)
    {
        if (check_philo_dead(philos) == 1 || philo_full(philos) == 1)
            return (NULL);
    }
}
