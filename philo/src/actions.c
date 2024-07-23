/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:22:36 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/23 18:05:10 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	sleeping(t_philo *philo)
{
	size_t	time_now;

	print_message(philo, "is sleeping", philo->id);
	usleep(philo->config->to_sleep_ms * 1000);
}

void	eating(t_philo *philo)
{
	size_t	time_now;

	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork", philo->id);
	if (philo->config->num_philos == 1)
	{
		usleep(philo->config->to_die_ms * 1000);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork", philo->id);
	print_message(philo, "is eating", philo->id);
	pthread_mutex_lock(&philo->config->meals_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->config->meals_lock);
	usleep(philo->config->to_eat_ms * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
