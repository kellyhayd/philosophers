/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:44:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 17:17:02 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	size_t	last_meal;

	pthread_mutex_lock(&philo->config->meals_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->config->meals_lock);
	pthread_mutex_lock(&philo->config->dead_lock);
	if ((get_current_time() - last_meal) >= philo->config->to_die_ms
		|| philo->config->dead_flag == 1)
	{
		philo->config->dead_flag = 1;
		return (pthread_mutex_unlock(&philo->config->dead_lock), 1);
	}
	pthread_mutex_unlock(&philo->config->dead_lock);
	return (0);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (!dead_loop(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (args);
}

void	start_threads(t_philo *philos, t_config *config)
{
	int			i;
	pthread_t	waiter;

	if (pthread_create(&waiter, NULL, monitor_routine, philos) != 0)
		destroy_all_mutex(philos);
	i = 0;
	while (i < config->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine,
				&philos[i]) != 0)
			destroy_all_mutex(philos);
		i++;
	}
	if (pthread_join(waiter, NULL) != 0)
		destroy_all_mutex(philos);
	i = 0;
	while (i < config->num_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			destroy_all_mutex(philos);
		i++;
	}
}
