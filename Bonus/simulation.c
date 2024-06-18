#include "philo_bonus.h"

static void    create_philo_process(t_simulation *simulation)
{
    int i;
    t_philo *p;

    p = simulation->philos;
    i = 0;
    while (i < simulation->philo_nbr)
    {
        p[i].pid = safe_fork(simulation);
        if (p[i].pid == 0)
        {
            //in philo/child process
            philo_routine(simulation, &p[i]);
            exit(0);
        }
        i++;
        //precise_usleep(100);
    }
}

static void    *monitor_full(void *data)
{
    t_simulation    *simulation;
    t_philo *philos;

    simulation = ((t_philo *)data)->simulation;
    philos = simulation->philos;
    while (1)
    {
        sem_wait(simulation->full);
        simulation->philos_full++;
        if (simulation->philos_full == simulation->philo_nbr)
        {
            sem_post(simulation->endsimul);
            return (NULL);
        }
    }
}

void    start_simulation(t_simulation *simulation)
{
    pthread_t   monitor;

    safe_thread(&monitor, monitor_full, (void *)&(simulation->philos[0]), CREATE);
    safe_thread(&monitor, NULL, simulation, DETACH);
    simulation->start_time = get_current_time() * 1e3;
    //sem_wait(simulation->endsimul);
    create_philo_process(simulation);
    sem_wait(simulation->endsimul);
    //test
    printf("signal received, ready to shut all down\n");
    //
    destroy_all(simulation);
    //test
    printf("detroyed all\n");
    //
}