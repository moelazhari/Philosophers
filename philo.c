#include "philo.h"


void *philosopher(void *val)
{
    int *i;
    *i = (int)val;



    return (i);
}

int main(int ac, char **av)
{
    t_philo p[atoi(av[1])];
    int i;

    if (ac != 5)
    {
        i = 0;
        while (i < 5)
        {
        pthread_mutex_init(&p[i].foork, NULL);
        pthread_create(&p[i].philo, NULL, (void *)philosopher, (void *)p);
        pthread_join(p[i].philo, NULL);
        }
    }
    return (0);
}