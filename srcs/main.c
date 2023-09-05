/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edupless <edupless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:35:09 by edupless          #+#    #+#             */
/*   Updated: 2023/08/28 13:41:58 by edupless         ###   ########.fr       */
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


long	ft_atoi(const char *str)
{
	int		i;
	long	rest;
	int		sign;

	i = 0;
	rest = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			rest = rest * 10 + str[i] - '0';
		else
			break ;
		i++;
	}
	return (sign * rest);
}

int	check_valid_input(int ac, char **av)
{
	int	i;
	int	check;

	i = 1;
	if (check_digit(ac, av) == 1)
		return (printf("Error other then digits\n"), 1);
	if (check_max_int(ac, av) == 1)
		return (printf("Error max int\n"), 1);
	while (i < ac)
	{
		check = ft_atoi(av[i]);
		if (i == 1 && (check <= 0 || check > 200))
			return (printf("Error more then the allowed phil\n"), 1);
		if ((i > 1 && i < 5) && (check < 60))
			return (printf("error you've entered a time < 60\n"), 1);
		i++;
	}
	return (0);
}

int	check_max_int(int ac, char **av)
{
	long	num;
	int		i;

	i = 1;
	(void)ac;
	while (av[i])
	{
		num = ft_atoi(av[i]);
		if (num > 2147483647 || num < -2147483648)
			return (1);
		i++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	check_digit(int ac, char **av)
{
	int	i;
	int	j;

	(void)ac;
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if(!(ft_isdigit(av[i][j])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

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

int   initiate_philo(t_var *var)
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

time_t	get_time_in_ms(void)
{
	time_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}


void	ft_1_philo(t_phil *phil)
{	
	int timed ;

	timed = (phil->var->time_to_die) * 1000 - 1000;
	
	pthread_mutex_lock(&phil->var->forks[phil->taking_fork]);
	printf("%ld %d %s\n", get_time_in_ms() - phil->var->start_time, phil->position, "has taken a fork");
	
	usleep(timed);
	phil->var->index_of_the_phil_who_died = phil->position;
	phil->var->time_of_death = get_time_in_ms() - phil->var->start_time;
	phil->var->stop_sign = 1;
}
 
void    *application(void *data)
{
	t_phil	*phil;

	phil = (t_phil *)data;
	if (phil->var->num_phil == 1)
	{
		ft_1_philo(phil);
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
		
		if (get_time_in_ms() - phil->last_time_ate >= phil->var->time_to_die \
				&& !phil->var->stop_sign)
		{
			phil->var->stop_sign = 1;
			phil->var->index_of_the_phil_who_died = phil->position;
			phil->var->time_of_death = get_time_in_ms() - phil->var->start_time;
			return (ft_unlock(phil), 1);
		}
		if (phil->var->stop_sign)
		usleep(100);
	}
	return (0);
}

int	main(void)
{
	int ac = 5 ;
	char *av[] = {"","4","1000","100","100",NULL};

	t_var	var;

	if (ac - 1 == 4)
	{
		if (check_valid_input(ac, av))
			return (1);

		fill_struct(av, &var);
		initiate_struct(&var);
		start_simulation(&var);
	}
	else
		printf("number_of_philosophers, time_to_die,\
		time_to_eat, time_to_sleep");
	return (0);
}

