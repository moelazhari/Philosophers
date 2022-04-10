/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:26:27 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/10 22:15:04 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 6 && ac != 5)
	{
		printf("./philo [number_of_philosophers] [time_to_die time_to_eat]");
		printf("[time_to_sleep]\n[number_of_times_each_philosopher_must_eat]");
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

int	main(int ac, char **av)
{
	int		i;
	t_data	data;

	i = -1;
	if (check_args(ac, av))
		return (1);
	unlink_semaphores();
	if (data_init(&data, av))
		return (1);
	while (++i < data.nbr_of_philo)
		sem_wait(data.finish);
	return (exit_program(&data));
}
