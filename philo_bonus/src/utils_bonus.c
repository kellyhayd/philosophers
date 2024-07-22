/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:15:13 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 23:25:20 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message(t_philo *philo, char *str, int id)
{
	size_t	time_now;

	sem_wait(philo->config->action);
	time_now = get_current_time() - philo->config->init_time;
	if (!philo->config->dead_flag)
		printf("%u %d %s\n", time_now, philo->id, str);
	sem_post(philo->config->action);
}