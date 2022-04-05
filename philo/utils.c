/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:37 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/05 18:34:50 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	rus;
	int	vul;
	int	i;

	i = 0;
	vul = 1;
	rus = 0;
	while ((str[i] == ' ' || str[i] == '\f')
		|| (str[i] == '\n' || str[i] == '\r')
		|| (str[i] == '\t' || str[i] == '\v'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			vul *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rus = (rus * 10) + ((int)str[i] - '0');
		i++;
	}	
	return (vul * rus);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	time.tv_sec = time.tv_sec * 1000;
	time.tv_usec = time.tv_usec / 1000;
	return (time.tv_sec + time.tv_usec);
}

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