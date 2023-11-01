/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edupless <edupless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:42:38 by edupless          #+#    #+#             */
/*   Updated: 2023/10/31 19:43:43 by edupless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_1_philo(t_phil *phil)
{
	pthread_mutex_lock(&phil->var->forks[phil->taking_fork]);
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

void	*application(void *data)
{
	t_phil	*phil;

	phil = (t_phil *)data;
	if (phil->var->num_phil == 1)
	{
		ft_1_philo(phil);
	}
	else if (phil->position % 2 == 0)
	{
		usleep(150);
		ft_odd_phil(phil);
	}
	else
	{
		ft_odd_phil(phil);
	}
	return (NULL);
}

int	start_simulation(t_var *var)
{
	int	i;

	i = 0;
	var->start_time = get_time_in_ms();
	while (i < var->num_phil)
	{
		var->phil[i].last_time_ate = get_time_in_ms();
		if (pthread_create(&var->phil[i].thread, NULL, \
			&application, &var->phil[i]))
			return (printf("Error creating threads\n"), 1);
		i++;
	}
	i = 0;
	while (i < var->num_phil)
	{
		pthread_join(var->phil[i].thread, NULL);
		i++;
	}
	if (var->stop_sign == 1)
		printf ("%ld %d %s\n", get_time_in_ms() - var->start_time, \
				var->index_of_the_phil_who_died, "died");
	ft_free(var);
	return (0);
}

void	ft_odd_phil(t_phil *phil)
{
	while (phil->must_eat)
	{
		pthread_mutex_lock(&phil->var->forks[phil->taking_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->position, "has taken a fork");
		if(ft_is(phil))
			break ;
		printf("%d \n", phil->var->stop_sign);
		pthread_mutex_lock(&phil->var->forks[phil->sc_fork]);
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->position, "has taken a fork");
		printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, \
				phil->position, "is eating");
		phil->var->t = phil->var->t_v - phil->must_eat ;
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

int	main(int ac, char **av)
{
	t_var	var;

	if (ac == 5 || ac == 6)
	{
		if (check_valid_input(ac, av))
			return (1);
		fill_struct(ac, av, &var);
		initiate_struct(&var);
		start_simulation(&var);
	}
	else
		printf("number_of_philosophers, time_to_die,\
		time_to_eat, time_to_sleep,number_of_times_each_philosopher_must_eat");
	return (0);
}
