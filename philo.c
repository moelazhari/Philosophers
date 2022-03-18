#include "philo.h"

void eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->eat);
    philo->death_time = get_time() + philo->data->time_to_die;
    pthread_mutex_unlock(&philo->eat);
    print(*philo, "is\teating");
    philo->nbr_eat++;
    if (philo->nbr_eat == philo->data->nbr_must_eat)
        philo->data->finish_eat++;
    usleep((philo->data->time_to_eat * 1000));
}

void taken_a_fork(t_philo *philo)
{
    pthread_mutex_lock(&(philo)->fork);
    print(*philo, "has\ttaken\ta fork");
    if (philo->nbr == philo->data->nbr_of_philo - 1)
    {
        pthread_mutex_lock(&(philo - philo->nbr)->fork);
        print(*philo, "has\ttaken\ta fork");
        eating(philo);
        pthread_mutex_unlock(&(philo - philo->nbr)->fork);
    }
    else 
    {
        pthread_mutex_lock(&(philo + 1)->fork);
        print(*philo, "has\ttaken\ta fork");
        eating(philo);
        pthread_mutex_unlock(&(philo + 1)->fork);
    }
    pthread_mutex_unlock(&(philo)->fork);
}

void *death_fnc(void *p)
{
    t_philo *philo;

    philo = p;
    
    while (1)
    {
        pthread_mutex_lock(&philo->eat);
        if (get_time() < philo->death_time)
             pthread_mutex_unlock(&philo->eat);
        else
            break ;
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
	philo->death_time = get_time() + philo->data->time_to_die;
    pthread_create(&death, NULL, &death_fnc, philo);
    pthread_detach(death);
    while (1)
    {
        print(*philo, "is\ttenking");
        taken_a_fork(philo);
        if (philo->nbr_eat == philo->data->nbr_must_eat)
            return (NULL);
        print(*philo, "is\tsleaping");
        usleep((philo->data->time_to_sleep * 1000));
    }
    return (NULL);
}