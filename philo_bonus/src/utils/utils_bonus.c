/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:37 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/11 02:32:54 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(unsigned long time, unsigned long start)
{
	usleep(time * 1000 * 0.95);
	while (get_time() - start < time)
		usleep(100);
}

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
		kill(data->p[i].pid, SIGKILL);
	sem_close(data->forks);
	sem_close(data->p->eat);
	sem_close(data->finish);
	sem_close(data->print);
	free(data->p);
	return (0);
}
