/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:37:37 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/01 14:42:49 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_close(data->print);
	sem_close(data->finish);
	unlink_semaphores();
	free(data->p);
	exit(0);
}
