/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:29 by mazhari           #+#    #+#             */
/*   Updated: 2022/03/28 20:42:34 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	time.tv_sec = time.tv_sec * 1000;
	time.tv_usec = time.tv_usec / 1000;
	return (time.tv_sec + time.tv_usec);
}

int	philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_of_philo)
	{
		data->p[i].nbr = i;
		data->p[i].data = data;
		data->p[i].nbr_eat = 0;
		pthread_mutex_init(&data->p[i].fork, NULL);
		pthread_mutex_init(&data->p[i].eat, NULL);
	}
	i = -1;
	data->start_time = get_time();
	while (++i < data->nbr_of_philo)
	{
		pthread_create(&data->p[i].philo, NULL, &philosopher, &data->p[i]);
		pthread_detach(data->p[i].philo);
	}
	return (0);
}

int	data_init(t_data *data, char **av)
{
	int	i;

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
		data->nbr_must_eat = 0;
	data->p = malloc(sizeof(data->p) * data->nbr_of_philo);
	if (!data->p)
	{
		printf("MALLOC ERROR");
		return (1);
	}
	pthread_mutex_init(&data->print, NULL);
	philo_init(data);
	return (0);
}
