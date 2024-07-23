/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 08:18:23 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/23 18:48:29 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_init(t_philo *philo, t_config *config)
{
	int	i;
	int	num_philo;

	num_philo = config->num_philos;
	i = 0;
	while (i < num_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_current_time();
		philo[i].config = config;
		i++;
	}
}

int	semaphores_init(t_config *config)
{
	sem_unlink("philo_fork");
	sem_unlink("philo_action");
	config->fork = sem_open("philo_fork", O_CREAT, 0700, config->num_philos);
	config->action = sem_open("philo_action", O_CREAT, 0700, 1);
	if (config->fork == SEM_FAILED || config->action == SEM_FAILED)
	{
		destroy_semaphores(config);
		return (0);
	}
	return (1);
}

void	config_init(t_config *config, char **argv)
{
	config->num_philos = convert_nbr(argv[1]);
	config->to_die_ms = convert_nbr(argv[2]);
	config->to_eat_ms = convert_nbr(argv[3]);
	config->to_sleep_ms = convert_nbr(argv[4]);
	if (argv[5])
		config->must_eat_times = convert_nbr(argv[5]);
	else
		config->must_eat_times = -1;
	config->init_time = get_current_time();
	config->dead_flag = 0;
}
