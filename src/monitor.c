/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:31:39 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 17:09:57 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals_eaten(t_philo *philos, t_config *config)
{
	int	finished_meals;
	int	i;

	if (config->must_eat_times == -1)
		return (0);
	i = 0;
	finished_meals = 0;
	pthread_mutex_lock(&config->meals_lock);
	while (i < config->num_philos)
	{
		if (philos[i].meals_eaten >= config->must_eat_times)
			finished_meals++;
		i++;
	}
	pthread_mutex_unlock(&config->meals_lock);
	if (finished_meals == config->num_philos)
	{
		pthread_mutex_lock(&config->dead_lock);
		config->dead_flag = 1;
		pthread_mutex_unlock(&config->dead_lock);
		return (1);
	}
	return (0);
}

int	check_death(t_philo *philos, t_config *config)
{
	int		i;
	size_t	time_now;

	i = 0;
	while (i < config->num_philos)
	{
		if (dead_loop(&philos[i]))
		{
			pthread_mutex_lock(&config->write_lock);
			time_now = get_current_time() - config->init_time;
			printf("%u %d died\n", time_now, philos[i].id);
			pthread_mutex_unlock(&config->write_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *args)
{
	t_philo		*philos;
	t_config	*config;

	philos = (t_philo *)args;
	config = philos[0].config;
	while (1)
		if (check_death(philos, config) || check_meals_eaten(philos, config))
			break ;
	return (args);
}
