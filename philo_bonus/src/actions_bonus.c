/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:41:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 23:52:45 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->config->fork);
	print_message(philo, "has taken a fork", philo->id);
	sem_wait(philo->config->fork);
	print_message(philo, "has taken a fork", philo->id);
	print_message(philo, "is eating", philo->id);
	philo->last_meal = get_current_time();
	usleep(philo->config->to_eat_ms * 1000);
	sem_post(philo->config->fork);
	sem_post(philo->config->fork);
	philo->meals_eaten++;
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is thinking", philo->id);
	usleep(philo->config->to_sleep_ms * 1000);
}

void	actions(t_philo *philo)
{
	while (!philo->config->dead_flag
		&& (philo->meals_eaten < philo->config->must_eat_times))
	{
		eating(philo);
		sleeping(philo);
		print_message(philo, "is thinking", philo->id);
	}
}

void	*check_life(void *args)
{
	t_philo *philo;
	philo = (t_philo *)args;
	size_t	last_meal;
	size_t	time_now;

	last_meal = philo->last_meal;
	time_now = get_current_time();
	if ((time_now - last_meal) >= philo->config->to_die_ms
		|| philo->config->dead_flag == 1)
	{
		philo->config->dead_flag = 1;
		sem_wait(philo->config->action);
		printf("%u %d died\n", time_now, philo->id);
		kill_process(philo);
		destroy_semaphores(philo->config);
	}
	return (NULL);
}