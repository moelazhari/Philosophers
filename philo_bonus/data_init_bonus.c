/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:29 by mazhari           #+#    #+#             */
/*   Updated: 2022/03/30 19:18:13 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	time.tv_sec = time.tv_sec * 1000;
	time.tv_usec = time.tv_usec / 1000;
	return (time.tv_sec + time.tv_usec);
}

void	*eat_fnc(void *vlu)
{
	int		i;
	t_data	*data;

	data = vlu;
	i = -1;
	while (++i < data->nbr_must_eat)
		sem_wait(data->finish);
	sem_post(data->check);
	return (0);
}

int	philo_init(t_data *data)
{
	int			i;
	int			pid;

	i = -1;
	data->p = malloc(sizeof(*data->p) * data->nbr_of_philo);
	if (!data->p)
	{
		printf("MALLOC ERROR");
		return (1);
	}
	data->start_time = get_time();
	while (++i < data->nbr_of_philo)
	{
		data->p[i].nbr = i;
		data->p[i].data = data;
		data->p[i].nbr_eat = 0;
		data->p[i].eat = sem_open("eat", O_CREAT, 0644, 1);
		pid = fork();
		if (pid == 0)
			philosopher(&data->p[i]);
		data->p[i].pid = pid;
	}
	return (0);
}

void	semaphores_init(t_data *data)
{
	data->forks = sem_open("forks", O_CREAT, 0644, data->nbr_of_philo);
	data->check = sem_open("check", O_CREAT, 0644, 0);
	data->print = sem_open("print", O_CREAT, 0644, 1);
	data->finish = sem_open("finish", O_CREAT, 0644, 0);
}

int	data_init(t_data *data, char **av)
{
	int			i;
	int			pid;
	pthread_t	eat;

	i = -1;
	pid = 1;
	data->nbr_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);	
	if (av[5])
	{
		data->nbr_must_eat = ft_atoi(av[5]);
		pthread_create(&eat, NULL, eat_fnc, data);
		pthread_detach(eat);
	}
	else
		data->nbr_must_eat = 0;
	semaphores_init(data);
	philo_init(data);
	return (0);
}
