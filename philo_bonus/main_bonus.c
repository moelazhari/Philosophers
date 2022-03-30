/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:26:27 by mazhari           #+#    #+#             */
/*   Updated: 2022/03/30 19:13:21 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 6 && ac != 5)
	{
		printf("./philo [number_of_philosophers] [time_to_die time_to_eat] [time_to_sleep]\n");
		printf("[number_of_times_each_philosopher_must_eat]");
		printf(" (the times input in milliseconds)\n");
		return (1);
	}
	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("all args must be a positive number\n");
				return (1);
			}
		}
	}
	return (0);
}

int	exit_program(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_of_philo)
		kill(data->p[i].pid, SIGKILL);
	sem_close(data->forks);
	sem_close(data->check);
	sem_close(data->print);
	sem_close(data->finish);
	sem_unlink("forks");
	sem_unlink("finish");
	sem_unlink("check");
	sem_unlink("print");
	sem_unlink("eat");
	free(data->p);
	exit(0);
}

void	unlink_semaphores(void)
{
	sem_unlink("eat");
	sem_unlink("forks");
	sem_unlink("finish");
	sem_unlink("check");
	sem_unlink("print");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av))
		return (1);
	unlink_semaphores();
	if (data_init(&data, av))
		return (1);
	sem_wait(data.check);
	return (exit_program(&data));
}
