/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:47 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/11 02:50:16 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->eat);
	print(*philo, "is eating");
	philo->death_time = get_time() + philo->data->time_to_die;
	philo->nbr_eat++;
	if (philo->nbr_eat == philo->data->nbr_must_eat)
		sem_post(philo->data->finish);
	sem_post(philo->eat);
	ft_usleep(philo->data->time_to_eat, get_time());
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
	int		i;

	philo = p;
	i = -1;
	while (!philo->die)
	{
		sem_wait(philo->eat);
		if (get_time() >= philo->death_time)
		{
			philo->die = 1;
			print(*philo, "died");
			while (++i < philo->data->nbr_of_philo)
				sem_post(philo->data->finish);
		}
		else
			sem_post(philo->eat);
		usleep(100);
	}
	return (0);
}

void	philosopher(t_philo *philo)
{
	pthread_t	death;

	philo->death_time = philo->data->start_time + philo->data->time_to_die;
	pthread_create(&death, NULL, &death_fnc, philo);
	pthread_detach(death);
	if (philo->nbr % 2 != 0)
		usleep(100);
	while (1)
	{
		taken_a_forks(philo);
		print(*philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, get_time());
		print(*philo, "is thinking");
		usleep(100);
	}
}
