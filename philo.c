#include "philo.h"

void taken_a_fork(t_philo *philo)
{
    if (philo->nbr == 0)
    {
        pthread_mutex_lock(&(philo + (philo->data->nbr_of_philo - 1))->fork);
        print(*philo, "has\ttaken\ta fork");
        pthread_mutex_lock(&(philo)->fork);
        print(*philo, "has\ttaken\ta fork");
        print(*philo, "is\teating");
        philo->death_time = get_time() + philo->data->time_to_die;
        philo->nbr_eat++;
        usleep(philo->data->time_to_sleep);
        pthread_mutex_unlock(&(philo + (philo->data->nbr_of_philo - 1))->fork);
        pthread_mutex_unlock(&(philo)->fork);
    }
    else 
    {
        pthread_mutex_lock(&(philo)->fork);
        print(*philo, "has\ttaken\ta fork");
        pthread_mutex_lock(&(philo - 1)->fork);
        print(*philo, "has\ttaken\ta fork");
        print(*philo, "is\teating");
        philo->death_time = get_time() + philo->data->time_to_die;
        philo->nbr_eat++;
        usleep(philo->data->time_to_sleep);
        pthread_mutex_unlock(&(philo)->fork);
        pthread_mutex_unlock(&(philo - 1)->fork);
    }
}

void *death_fnc(void *p)
{
    t_philo *philo;

    philo = p;
    while (get_time() < philo->death_time)
    {
    }
    print(*philo, "is\tdeath");
    philo->data->death = 1;
    return (NULL);
}

void    *philosopher(void *p)
{
    t_philo *philo;
    pthread_t death;

    philo = p;
    philo->start_time = get_time();
	philo->death_time = philo->start_time + philo->data->time_to_die;
    pthread_create(&death, NULL, &death_fnc, philo);
    pthread_detach(death);
    while (philo->nbr_eat < philo->data->nbr_must_eat)
    {
        print(*philo, "is\ttenking");
        taken_a_fork(philo);
        print(*philo, "is\tsleaping");
        usleep(philo->data->time_to_sleep);
    }
    philo->data->finish_eat = 1;
    return (NULL);
}