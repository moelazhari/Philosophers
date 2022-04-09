/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:47 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/09 22:32:29 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	//sem_wait(philo->eat);
	philo->death_time = get_time() + philo->data->time_to_die;
	philo->nbr_eat++;
	if (philo->nbr_eat == philo->data->nbr_must_eat && philo->data->nbr_must_eat > 0)
		sem_post(philo->data->finish);
	print(*philo, "is eating");
	//sem_post(philo->eat);
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
	while (1)
	{
		sem_wait(philo->eat);
		if (get_time() >= philo->death_time)
		{
			philo->die = 1;
			print(*philo, "died");
			while (++i <  philo->data->nbr_of_philo)
				sem_post(philo->data->finish);
			return (0);
		}
		else
			sem_post(philo->eat);
		usleep(100);
	}
}

void	philosopher(t_philo *philo)
{
	pthread_t	death;

	philo->death_time = philo->data->start_time + philo->data->time_to_die;
	pthread_create(&death, NULL, &death_fnc, philo);
	if (philo->nbr % 2 == 0)
		ft_usleep(philo->data->time_to_eat, get_time());
	//pthread_detach(death);
	while (1)
	{
		print(*philo, "is thinking");
		taken_a_forks(philo);
		print(*philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, get_time());
		usleep(100);
	}
}
