#include "philo.h"

long get_time(){
	struct timeval	time;

	gettimeofday(&time, NULL);
	time.tv_sec = time.tv_sec * 1000;
	time.tv_usec = time.tv_usec / 1000;
	return (time.tv_sec + time.tv_usec);
}

int philo_init(t_data *data)
{
	int i;
    i = -1;

	data->p = malloc(sizeof(data->p) * data->nbr_of_philo);
    if (!data->p)
    	exit_program("MALLOC ERROR");
	data->p->nbr_eat = 0;
	while (++i < data->nbr_of_philo)
    {
        data->p[i].data = data;
        data->p[i].nbr = i;
        pthread_mutex_init(&data->p[i].fork, NULL);
        //pthread_mutex_init(&data->p[i].eat, NULL);
		pthread_create(&data->p[i].philo, NULL, &philosopher, &data->p[i]);
    }
	i = -1;
    while (++i < data->nbr_of_philo)
         pthread_detach(data->p[i].philo);
	return (0);
}

int data_init(t_data *data, char **av)
{
    int i;
    i = -1;

    data->nbr_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->death = 0;
	data->finish_eat = 0;
	if (av[5])
		data->nbr_must_eat = ft_atoi(av[5]);
	else
		data->nbr_must_eat = -1;
	if (philo_init(data))
		return (1);
	return (0);
}
