#include "philo.h"

//example of args: ./philo 5          500          200          200            [5]
//                         nbr_philos time_to_die  time_eating  time_sleeping  meals_tobe_full
int main(int argc, char **argv)
{
    t_simulation    simulation;

    if (argc == 5 || argc == 6)
    {
        //check if the args are valid numbers and fill some eles of the simulation structure with args
        check_args_and_fill(&simulation, argv);
        //init forks and philos
        data_init(&simulation);
        //start simulation: create and join threads
        start_simulation(&simulation);
        free_all(&simulation);
    }
    else
        error_exit("Pass the right amount of arguments.", NULL);
}
