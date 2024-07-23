/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:41:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/23 18:56:03 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_life(t_philo *philo)
{
	size_t	time_now;

	time_now = get_current_time();
	if ((time_now - philo->last_meal) >= philo->config->to_die_ms)
	{
		sem_wait(philo->config->action);
		printf("%zu %d died\n", time_now - philo->config->init_time, philo->id);
		return (0);
	}
	return (1);
}

void	thinking(t_philo *philo)
{
	size_t	time_now;
	size_t	to_think;

	to_think = philo->config->to_die_ms - philo->config->to_eat_ms \
		- philo->config->to_sleep_ms;
	if (to_think > 5)
		to_think = 5;
	else if (to_think < 0)
		to_think = 0;
	print_message(philo, "is thinking", philo->id);
	usleep(to_think * 1000);
}

void	actions(t_philo *philo)
{
	while (philo->meals_eaten < philo->config->must_eat_times
		|| philo->config->must_eat_times == -1)
	{
		sem_wait(philo->config->fork);
		if (!check_life(philo))
			break ;
		print_message(philo, "has taken a fork", philo->id);
		sem_wait(philo->config->fork);
		if (!check_life(philo))
			break ;
		print_message(philo, "has taken a fork", philo->id);
		print_message(philo, "is eating", philo->id);
		philo->last_meal = get_current_time();
		usleep(philo->config->to_eat_ms * 1000);
		sem_post(philo->config->fork);
		sem_post(philo->config->fork);
		philo->meals_eaten++;
		if (!check_life(philo))
			break ;
		print_message(philo, "is sleeping", philo->id);
		usleep(philo->config->to_sleep_ms * 1000);
		if (!check_life(philo))
			break ;
		thinking(philo);
	}
}
