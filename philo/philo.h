/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:26:34 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/05 22:20:01 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	eat;
	int				nbr_eat;
	int				nbr;
	long long		death_time;
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
	long long		start_time;
	int				death;
	int				finish_eat;
	pthread_mutex_t	print;
}				t_data;

int			ft_atoi(const char *str);
int			data_init(t_data *data, char **av);
void		*philosopher(void *p);
int			exit_program(t_data *data);
long long	get_time(void);
void		print(t_philo philo, char *str);

#endif 
