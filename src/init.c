/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 22:56:29 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/14 13:50:33 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philos, t_config *config, pthread_mutex_t *forks)
{
	int	i;
	
	i = 0;
	while (i < config->num_philos)
	{
		philos[i].config = config;
		philos[i].meals_eaten = 0;
		philos[i].id = i + 1;
		if (i == 0)
		{
			philos[i].l_fork = &forks[(i + 1) % config->num_philos];
			philos[i].r_fork = &forks[i];
		}
		else
		{
			philos[i].l_fork = &forks[i];
			philos[i].r_fork = &forks[(i + 1) % config->num_philos];
		}
		i++;
	}
}

void	init_config(t_config *config, char **argv)
{
	config->num_philos = convert_nbr(argv[1]);
	config->to_die_ms = convert_nbr(argv[2]);
	config->to_eat_ms = convert_nbr(argv[3]);
	config->to_sleep_ms = convert_nbr(argv[4]);
	if (argv[5])
		config->must_eat_times = convert_nbr(argv[5]);
	config->init_time = get_current_time();
}