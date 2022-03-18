#include "philo.h"

void print(t_philo  philo,  char *str)
{
    long time;

    time = get_time() - philo.data->start_time;
    pthread_mutex_lock(&philo.data->print);
    printf("%ld\t%d\t%s\n", time, philo.nbr + 1, str);
    pthread_mutex_unlock(&philo.data->print);
}

int exit_program(t_philo  *philo)
{
    return (0);
}