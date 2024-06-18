#include "philo_bonus.h"

static void    eat(t_philo *philo)
{
    sem_wait(philo->simulation->forks);
    sem_wait(philo->simulation->forks);
    print_message("has taken forks", philo);
    print_message("is eating", philo);
    sem_wait(philo->simulation->death_check);
    philo->meal_time = get_current_time() * 1e3 - philo->simulation->start_time;
    sem_post(philo->simulation->death_check);
    precise_usleep(philo->simulation->time_to_eat);
    sem_post(philo->simulation->forks);
    sem_post(philo->simulation->forks);
    philo->meals_eaten++;
    if (philo->simulation->max_meal != -1 && philo->meals_eaten >= philo->simulation->max_meal)
        sem_post(philo->simulation->full);
}

static void    nap_think(t_philo *philo)
{
    print_message("is sleeping", philo);
    precise_usleep(philo->simulation->time_to_sleep);
    print_message("is thinking", philo);
}


static void    *monitor_death(void *data)
{
    t_philo *p;

    p = (t_philo *)data;
    while (1)
    {
        sem_wait(p->simulation->death_check);
        if (get_current_time() * 1e3 - p->simulation->start_time - p->meal_time > p->simulation->time_to_die)
        {
            print_message("died", p);
            sem_post(p->simulation->endsimul);
            //test
            printf("sem post done, signal sent\n");
            //
            return (NULL);
        }
        sem_post(p->simulation->death_check);
        precise_usleep(500);
    }
}

void    philo_routine(t_simulation *simulation, t_philo *philo)
{
    pthread_t   monitor;

    safe_thread(&monitor, monitor_death, (void *)philo, CREATE);
    safe_thread(&monitor, NULL, (void *)simulation, DETACH);
    if (philo->philo_id % 2 == 0)
        precise_usleep(simulation->time_to_eat / 2);
    while (1)
    {
        eat(philo);
        nap_think(philo);
    }
}