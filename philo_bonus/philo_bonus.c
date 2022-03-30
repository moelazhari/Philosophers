/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:47 by mazhari           #+#    #+#             */
/*   Updated: 2022/03/30 18:37:48 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->eat);
	print(*philo, "is eating");
	philo->death_time = get_time() + philo->data->time_to_die;
	philo->nbr_eat++;
	if (philo->data->nbr_must_eat > 0
		&& philo->nbr_eat == philo->data->nbr_must_eat)
		sem_post(philo->data->finish);
	sem_post(philo->eat);
	usleep((philo->data->time_to_eat * 1000));
}

void	taken_a_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print(*philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print(*philo, "has taken a fork");
	eating(philo);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	*death_fnc(void *p)
{
	t_philo	*philo;
	int		time;
	int		i;

	philo = p;
	while (1)
	{
		if (get_time() >= philo->death_time)
		{
			print(*philo, "died");
			sem_wait(philo->eat);
			sem_post(philo->data->check);
			return (0);
		}
	}
}

void	philosopher(t_philo *philo)
{
	pthread_t	death;

	philo->death_time = get_time() + philo->data->time_to_die;
	pthread_create(&death, NULL, &death_fnc, philo);
	pthread_detach(death);
	while (1)
	{
		print(*philo, "is thinking");
		taken_a_forks(philo);
		print(*philo, "is sleeping");
		usleep((philo->data->time_to_sleep * 1000));
	}
}