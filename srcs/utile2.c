/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edupless <edupless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:06:56 by edupless          #+#    #+#             */
/*   Updated: 2023/10/31 19:42:11 by edupless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
}

void	ft_unlock(t_phil *phil)
{
	pthread_mutex_unlock(&phil->var->forks[phil->sc_fork]);
	pthread_mutex_unlock(&phil->var->forks[phil->taking_fork]);
}

bool phis(t_phil *phil)
{
if (phil->var->time_to_die >= phil->var->time_to_eat + phil->var->time_to_sleep )
		return (false);
return (true); 
} 

bool 	ft_is(t_phil *phil)
{
	if (!phis (phil))
		{
			phil->var->stop_sign = 1;
			phil->var->index_of_the_phil_who_died = phil->position;
			phil->var->time_of_death = get_time_in_ms() - phil->var->start_time;
			return (ft_unlock(phil), 1);
			return(false);
		}
		if (phil->var->stop_sign)
			usleep(10);
	
return (true);
}
