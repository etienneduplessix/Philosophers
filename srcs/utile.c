/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edupless <edupless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:41:59 by edupless          #+#    #+#             */
/*   Updated: 2023/10/31 16:39:36 by edupless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	philod(t_phil *phil)
{
	usleep (100);
	if (phil->var->t > 8 && phil->var->s == 10)
		return (false);
	return (true);
}

int	ft_sleep(t_phil *phil, long time)
{
	long	now;

	now = get_time_in_ms();
	while (get_time_in_ms() - now < time)
	{
		if (!philod (phil))
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
