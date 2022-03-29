/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:26:34 by mazhari           #+#    #+#             */
/*   Updated: 2022/03/29 15:48:53 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct s_philo
{
	sem_t			*eat;
	int				nbr;
	int				nbr_eat;
	int				pid;
	long			death_time;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	t_philo			*p;
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_must_eat;
	long			start_time;
	int				finish_eat;
	sem_t			*death;
	sem_t			*forks;
	sem_t			*print;
}				t_data;

int		ft_atoi(const char *str);
int		data_init(t_data *data, char **av);
void	philosopher(t_philo *philo);
long	get_time(void);
void	print(t_philo philo, char *str);

#endif 
