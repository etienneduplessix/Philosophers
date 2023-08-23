
#include"../include/philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}



void	ft_free(t_var *var)
{
	free(var->phil);
	free(var->forks);
	free(var->log);
	free(var->meal);
}

void	ft_just_unlock(t_phil *phil)
{
	pthread_mutex_unlock(phil->var->meal);
	pthread_mutex_unlock(&phil->var->forks[phil->sc_fork]);
	pthread_mutex_unlock(&phil->var->forks[phil->fr_fork]);
}

void	ft_lone_ranger(t_phil *phil)
{
	pthread_mutex_lock(&phil->var->forks[phil->fr_fork]);
	printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
			phil->position, "has taken a fork");
	while (1)
	{
		if (get_time_in_ms() - phil->last_time_ate > phil->var->time_to_die)
		{
			phil->var->index_of_the_phil_who_died = phil->position;
			phil->var->time_of_death = get_time_in_ms() - phil->var->start_time;
			phil->var->stop_sign = 1;
			break ;
		}
	}
}
