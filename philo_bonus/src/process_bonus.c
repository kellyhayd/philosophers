/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:49:27 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 23:51:36 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->config->num_philos)
	{
		kill(philo[i].pid, SIGINT);
		i++;
	}
}

void	create_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->config->num_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			philo_threads(philo, i);
		i++;
	}
}

