/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:47 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/01 14:50:23 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat);
	print(*philo, "is eating");
	philo->death_time = get_time() + philo->data->time_to_die;
	philo->nbr_eat++;
	if (philo->nbr_eat == philo->data->nbr_must_eat)
		philo->data->finish_eat++;
	pthread_mutex_unlock(&philo->eat);
	usleep((philo->data->time_to_eat * 1000));
}

void	taken_a_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo)->fork);
	print(*philo, "has taken a fork");
	if (philo->nbr == philo->data->nbr_of_philo - 1)
	{
		pthread_mutex_lock(&(philo - philo->nbr)->fork);
		print(*philo, "has taken a fork");
		eating(philo);
		pthread_mutex_unlock(&(philo - philo->nbr)->fork);
		pthread_mutex_unlock(&(philo)->fork);
	}
	else
	{
		pthread_mutex_lock(&(philo + 1)->fork);
		print(*philo, "has taken a fork");
		eating(philo);
		pthread_mutex_unlock(&(philo + 1)->fork);
		pthread_mutex_unlock(&(philo)->fork);
	}
}

void	*death_fnc(void *p)
{
	t_philo	*philo;
	int		time;

	philo = p;
	while (1)
	{
		if (get_time() >= philo->death_time)
		{
			pthread_mutex_lock(&philo->eat);
			philo->data->death = 1;
			print(*philo, "died");
			return (NULL);
		}
	}
}

void	*philosopher(void *p)
{
	t_philo		*philo;
	pthread_t	death;

	philo = p;
	philo->death_time = get_time() + philo->data->time_to_die;
	pthread_create(&death, NULL, &death_fnc, philo);
	pthread_detach(death);
	while (1)
	{
		print(*philo, "is thinking");
		taken_a_fork(philo);
		if (philo->nbr_eat == philo->data->nbr_must_eat)
			return (NULL);
		print(*philo, "is sleeping");
		usleep((philo->data->time_to_sleep * 1000));
	}
	return (NULL);
}
