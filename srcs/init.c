/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edupless <edupless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:41:37 by edupless          #+#    #+#             */
/*   Updated: 2023/09/06 16:23:06 by edupless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	initiate_struct(t_var *var)
{
	var->phil = malloc(sizeof(t_phil) * var->num_phil);
	var->forks = malloc(sizeof(pthread_mutex_t) * var->num_phil);
	var->log = malloc(sizeof(pthread_mutex_t));
	if (initiate_mutexeses(var) == 1 || initiate_philo(var) == 1)
	{
		free(var->phil);
		free(var->forks);
		return (0);
	}
	return (1);
}

int	initiate_philo(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->num_phil)
	{
		var->phil[i].times_ate = 0;
		var->phil[i].position = i + 1;
		var->phil[i].taking_fork = i;
		var->phil[i].sc_fork = (i + 1) % var->num_phil;
		var->phil[i].var = var;
		var->phil[i].must_eat = 100000000;
		i++;
	}
	return (0);
}

int	initiate_mutexeses(t_var *var)
{
	int	i;

	i = 0;
	while (i < var->num_phil)
	{
		if (pthread_mutex_init(&var->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(var->log, NULL))
		return (1);
	return (0);
}

void	fill_struct(char **av, t_var *var)
{
	var->num_phil = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	var->time_of_death = 0;
	var->index_of_the_phil_who_died = 0;
}