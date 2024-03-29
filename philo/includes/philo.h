/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 14:26:34 by mazhari           #+#    #+#             */
/*   Updated: 2022/04/10 23:19:23 by mazhari          ###   ########.fr       */
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
	pthread_mutex_t	leftfork;
	pthread_mutex_t	*rightfork;
	pthread_mutex_t	eat;
	int				nbr_eat;
	int				nbr;
	unsigned long	death_time;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	t_philo			*p;
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_must_eat;
	unsigned long	start_time;
	int				death;
	int				finish_eat;
	pthread_mutex_t	print;
}				t_data;

int		ft_atoi(const char *str);
int		data_init(t_data *data, char **av);
void		*philosopher(void *p);
int		exit_program(t_data *data);
unsigned long	get_time(void);
void		ft_usleep(unsigned long time, unsigned long start);
void		print(t_philo philo, char *str);

#endif 
