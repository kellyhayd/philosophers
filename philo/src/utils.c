/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:43:47 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/23 17:46:42 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_mutex(t_philo *philos)
{
	int	i;

	pthread_mutex_destroy(&philos->config->dead_lock);
	pthread_mutex_destroy(&philos->config->write_lock);
	pthread_mutex_destroy(&philos->config->meals_lock);
	i = 0;
	while (i < philos->config->num_philos)
	{
		pthread_mutex_destroy(&philos->config->forks[i]);
		i++;
	}
}

void	print_message(t_philo *philo, char *str, int id)
{
	size_t	time_now;

	pthread_mutex_lock(&philo->config->write_lock);
	time_now = get_current_time() - philo->config->init_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time_now, philo->id, str);
	pthread_mutex_unlock(&philo->config->write_lock);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	convert_nbr(char *str)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	if (str[0] == '-')
		return (write(2, "Arguments must be positive integers\n", 36), -1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (write(2, "Arguments must be integers\n", 27), -1);
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	if (nbr == 0)
		return (-1);
	return (nbr);
}
