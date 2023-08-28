
#include"../include/philo.h"

int	start_simulation(t_var *var)
{
	int	i;

	i = 0;
	var->start_time = get_time_in_ms();
	while (i < var->num_phil)
	{
		var->phil[i].last_time_ate = get_time_in_ms();
		if (pthread_create(&var->phil[i].thread, NULL, &application, &var->phil[i]))
			return (printf("Error creating threads\n"), 1);
		i++;
	}
	i = 0;
	{
		pthread_join(var->phil[i].thread, NULL);
		i++;
	}
	if (var->stop_sign == 1)
		printf("%ld %d %s\n", get_time_in_ms() - var->start_time, \
				var->index_of_the_phil_who_died, "died");
	ft_free(var);
	return (0);
}

void	*application(void *data)
{
	t_phil	*phil;

	phil = (t_phil *)data;
	if (phil->var->num_phil == 1)
	{
		ft_lone_ranger(phil);
		return (NULL);
	}
	if (phil->position % 2 == 0)
		usleep(200);
	ft_odd_phil(phil);
	return (NULL);
}

void	ft_odd_phil(t_phil *phil)
{
	while (phil->must_eat)
	{
		pthread_mutex_lock(&phil->var->forks[phil->taking_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->position, "has taken a fork");
		pthread_mutex_lock(&phil->var->forks[phil->sc_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->position, "has taken a fork");
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->position, "is eating");
		if (ft_sleep(phil, phil->var->time_to_eat))
			break ;
		phil->last_time_ate = get_time_in_ms();
		pthread_mutex_unlock(&phil->var->forks[phil->sc_fork]);
		pthread_mutex_unlock(&phil->var->forks[phil->taking_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->position, "is sleeping");
		if (ft_sleep(phil, phil->var->time_to_sleep))
			break ;
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->position, "is thinking");
		phil->must_eat--;
	}
}

int	ft_sleep(t_phil *phil, long time)
{
	long	now;

	now = get_time_in_ms();
	while (get_time_in_ms() - now < time)
	{
		pthread_mutex_lock(phil->var->meal);
		if (get_time_in_ms() - phil->last_time_ate >= phil->var->time_to_die \
				&& !phil->var->stop_sign)
		{
			phil->var->stop_sign = 1;
			phil->var->index_of_the_phil_who_died = phil->position;
			phil->var->time_of_death = get_time_in_ms() - phil->var->start_time;
			return (ft_unlock(phil), 1);
		}
		if (phil->var->stop_sign)
			return (ft_unlock(phil), 1);
		pthread_mutex_unlock(phil->var->meal);
		usleep(100);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_var	var;

	if (ac - 1 == 4 )
	{
		if (check_valid_input(ac, av))
			return (1);
		fill_struct(av,&var);
		initiate_struct(&var);
		start_simulation(&var);
	}
	else
		printf("number_of_philosophers, time_to_die, time_to_eat, time_to_sleep");
	return (0);
}
