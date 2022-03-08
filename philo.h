#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t foork;
}              t_philo;