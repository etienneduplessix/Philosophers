/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etienneduplessix <etienneduplessix@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:41:59 by edupless          #+#    #+#             */
/*   Updated: 2023/10/18 15:04:41 by etiennedupl      ###   ########.fr       */
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




bool philod(t_phil *phil)
{
usleep(10);
if((var->phil->time) - (phil->times_ate + phil->var->time_to_sleep) <= 10 )
	return(false);
return(true);
}

int	ft_sleep(t_phil *phil, long time)
{
	long	now;
	
	now = get_time_in_ms();
	while (get_time_in_ms() - now < time)
	{
		
		if(!philod(phil))
		{
			phil->var->stop_sign = 1;
			phil->var->index_of_the_phil_who_died = phil->position;
			phil->var->time_of_death = get_time_in_ms() - phil->var->start_time;
			return (ft_unlock(phil), 1);
		}
		
		if (phil->var->stop_sign)
			usleep(10);
	}
	return (0);
}

time_t	get_time_in_ms(void)
{
	time_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
time_t	get_time_in_mc(long ti)
{
	time_t			time;
	
	time = ti ;
return (time);
}


