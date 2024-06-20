#include "philo_bonus.h"

int main(int argc, char **argv)
{
    t_simulation    simulation;

    if (argc == 5 || argc == 6)
    {
        check_args_and_fill(&simulation, argv);
        data_init(&simulation);
        start_simulation(&simulation);
    }
    else
        error_exit("Pass the right amount of arguments.", NULL);
}