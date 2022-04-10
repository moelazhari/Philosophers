/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:47 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/10 20:32:56 by mazhari          ###   ########.fr       */
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
	ft_usleep(philo->data->time_to_eat, get_time());
}

void	taken_a_fork(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->nbr;
	right_fork = (philo->nbr + 1) % philo->data->nbr_of_philo;
	pthread_mutex_lock(&philo[left_fork].fork);
	print(*philo, "has taken a fork");
	pthread_mutex_lock(&philo[right_fork].fork);
	print(*philo, "has taken a fork");
	eating(philo);
	pthread_mutex_unlock(&philo[left_fork].fork);
	pthread_mutex_unlock(&philo[right_fork].fork);
}

void	*philosopher(void *p)
{
	t_philo		*philo;

	philo = p;
	philo->death_time = philo->data->start_time + philo->data->time_to_die;
	while (1)
	{
		taken_a_fork(philo);
		if (philo->nbr_eat == philo->data->nbr_must_eat)
			break ;
		print(*philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep, get_time());
		print(*philo, "is thinking");
		usleep(50);
	}
	return (NULL);
}
