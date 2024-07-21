/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:22:36 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 14:30:55 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	died(t_philo *philo)
{
	size_t	time_now;

	time_now = get_current_time() - philo->config->init_time;
	if (get_dead_flag(philo))
		return ;
	else
	{
		pthread_mutex_lock(&philo->config->dead_lock);
		philo->config->dead_flag = 1;
		printf("%u %d died\n", time_now, philo->id);
		pthread_mutex_unlock(&philo->config->dead_lock);
	}
}

void	thinking(t_philo *philo)
{
	size_t	time_now;

	print_message(philo, "is thinking", philo->id);
}

void	sleeping(t_philo *philo)
{
	size_t	time_now;

	// time_now = get_current_time() - philo->config->init_time;
	// if (!get_dead_flag(philo))
	// {
	// 	printf("%u %d is sleeping\n", time_now, philo->id);
	// 	usleep(philo->config->to_sleep_ms * 1000);
	// }
	print_message(philo, "is sleeping", philo->id);
	usleep(philo->config->to_sleep_ms * 1000);
}

void	eating(t_philo *philo)
{
	size_t	time_now;

	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork", philo->id);
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
