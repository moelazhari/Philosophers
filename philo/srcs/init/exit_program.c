/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:37 by mazhari           #+#    #+#             */
/*   Updated: 2022/03/31 18:41:27 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo philo, char *str)
{
	long	time;

	time = get_time() - philo.data->start_time;
	pthread_mutex_lock(&philo.data->print);
	printf("%ld\t%d\t%s\n", time, philo.nbr + 1, str);
	if (!philo.data->death
		&& philo.data->finish_eat != philo.data->nbr_of_philo)
		pthread_mutex_unlock(&philo.data->print);
}

int	exit_program(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(&data->p[i].fork);
		pthread_mutex_destroy(&data->p[i].eat);
	}
	pthread_mutex_destroy(&data->print);
	i = -1;
	free(data->p);
	return (1);
}
