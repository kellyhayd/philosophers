/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:15:13 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/23 18:20:13 by krocha-h         ###   ########.fr       */
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
	printf("%zu %d %s\n", time_now, philo->id, str);
	sem_post(philo->config->action);
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
	if (nbr <= 0)
		return (-1);
	return (nbr);
}

void	destroy_semaphores(t_config *config)
{
	sem_close(config->fork);
	sem_close(config->action);
	sem_unlink("philo_forks");
	sem_unlink("philo_action");
}
