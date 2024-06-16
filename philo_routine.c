#include "philo.h"

static bool    end_simulation(t_simulation *simulation)
{
    bool    res;

    res = false;
    safe_mutex(&(simulation->endsimul_lock), LOCK, simulation);
    if (simulation->end_simulation == true)
        res = true;
    safe_mutex(&(simulation->endsimul_lock), UNLOCK, simulation);
    return (res);
}

static void eating(t_philo *philo)
{
    t_simulation    *simulation;

    simulation = philo->simulation;
    print_message("has taken a fork", philo);
    print_message("is eating.", philo);
    safe_mutex(&(simulation->mealtime_lock), LOCK, simulation);
    philo->meal_time = get_current_time() * 1000 - simulation->start_time;
    safe_mutex(&(simulation->mealtime_lock), UNLOCK, simulation);
    precise_usleep(simulation->time_to_eat);
}

static int eat(t_philo *philo)
{
    t_simulation    *simulation;

    simulation = philo->simulation;    
    if (simulation->philo_nbr == 1)
    {
        precise_usleep(simulation->time_to_die);
        return (1);
    }
    safe_mutex(&(philo->right_fork->fork), LOCK, simulation);
    safe_mutex(&(philo->left_fork->fork), LOCK, simulation);
    if (end_simulation(philo->simulation))
    {
        safe_mutex(&(philo->left_fork->fork), UNLOCK, simulation);
        safe_mutex(&(philo->right_fork->fork), UNLOCK, simulation);
        return (1);
    }
    eating(philo);
    safe_mutex(&(philo->right_fork->fork), UNLOCK, simulation);
    safe_mutex(&(philo->left_fork->fork), UNLOCK, simulation);
    safe_mutex(&(simulation->mealnum_lock), LOCK, simulation);
    philo->meals_eaten++;
    safe_mutex(&(simulation->mealnum_lock), UNLOCK, simulation);
    return (0);
}

static void nap_think(t_philo *philo)
{
    t_simulation    *simulation;

    simulation = philo->simulation;
    if (end_simulation(simulation))
        return ;
    print_message("is sleeping.", philo);
    precise_usleep(simulation->time_to_sleep);
    if (end_simulation(philo->simulation))
        return ;
    print_message("is thinking.", philo);
}

void    *philo_routine(void *philo)
{
    t_philo *p;
    
    p = (t_philo *)philo;
    if (p->philo_id % 2 == 0)
        precise_usleep(p->simulation->time_to_eat / 2);
    while (1)
    {
        if (end_simulation(p->simulation))
            break;
        if (eat(philo) == 0)
            nap_think(philo);
        else
            break;
    }
    return (NULL);
}