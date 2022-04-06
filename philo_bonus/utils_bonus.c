/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:37 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/06 02:38:24 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

long	get_time(void)
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
	sem_wait(philo.data->print);
	printf("%ld\t%d\t%s\n", time, philo.nbr + 1, str);
	if (!philo.die)
		sem_post(philo.data->print);
}

void	unlink_semaphores(void)
{
	sem_unlink("forks");
	sem_unlink("eat");
	sem_unlink("finish");
	sem_unlink("print");
}

int	exit_program(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_of_philo)
	{
		kill(data->p[i].pid, SIGKILL);
		sem_close(data->p[i].eat);
	}
	sem_close(data->forks);
	sem_close(data->print);
	sem_close(data->finish);
	unlink_semaphores();
	free(data->p);
	exit(0);
}
