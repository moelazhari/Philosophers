#include "philo.h"

int print(t_philo  philo,  char *str)
{
    printf("%ld\t%d\t%s\n", get_time() - philo.start_time, philo.nbr + 1, str);
    return (0); 
}

int exit_program(char *str)
{
    printf("%s", str);
    return (1);
}