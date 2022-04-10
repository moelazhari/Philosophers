/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:29 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/10 21:53:36 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_fnc(void *info)
{
	t_data	*data;
	int		i;

	data = info;
	i = -1;
	while (!data->death)
	{
		while (++i < data->nbr_of_philo && !data->death)
		{
			if (data->p[i].nbr_eat == data->nbr_must_eat)
				break ;
			pthread_mutex_lock(&data->p[i].eat);
			if (get_time() >= data->p[i].death_time)
			{
				print(data->p[i], "died");
				data->death = 1;
			}
			else
				pthread_mutex_unlock(&data->p[i].eat);
		}
		i = -1;
		usleep(50);
	}
	return (NULL);
}

int	philo_init(t_data *data)
{
	pthread_t	death;
	int			i;

	i = -1;
	while (++i < data->nbr_of_philo)
	{
		pthread_mutex_init(&data->p[i].fork, NULL);
		pthread_mutex_init(&data->p[i].eat, NULL);
	}
	i = -1;
	data->start_time = get_time();
	while (++i < data->nbr_of_philo)
	{
		data->p[i].nbr = i;
		data->p[i].data = data;
		data->p[i].nbr_eat = 0;
		pthread_create(&data->p[i].philo, NULL, &philosopher, &data->p[i]);
		pthread_detach(data->p[i].philo);
	}
	pthread_create(&death, NULL, &death_fnc, data);
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
		data->nbr_must_eat = -1;
	data->p = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!data->p)
	{
		printf("MALLOC ERROR");
		return (1);
	}
	pthread_mutex_init(&data->print, NULL);
	philo_init(data);
	return (0);
}
