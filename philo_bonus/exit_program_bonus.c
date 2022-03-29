/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:37 by mazhari           #+#    #+#             */
/*   Updated: 2022/03/29 15:37:10 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print(t_philo philo, char *str)
{
	long	time;

	time = get_time() - philo.data->start_time;
	sem_wait(philo.data->print);
	printf("%ld\t%d\t%s\n", time, philo.nbr + 1, str);
	sem_post(philo.data->print);
}

/*
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
*/