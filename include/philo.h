/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:27:58 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/04 11:32:07 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

/**
 * @brief Struct that contains the arguments that define the program parameters
 * 
 * @var nbr_of_philos: The number of philos and also the number of forks
 * @var to_die_ms: Time in milliseconds that if a philosopher don't
 * 		start to eat, they die;
 * @var to_eat_ms: Time in milliseconds it takes for a philosopher to eat
 * @var to_sleep_ms: Time in milliseconds a philosopher will spend sleeping
 * @var must_eat_times (optional): If all philos have eaten at least
 * 		must_eat_times, the simulation stops. If not specified,
 * 		the simulation stops when a philo dies. 
 */
typedef struct	s_config
{
	int	num_philos;
	int	to_die_ms;
	int	to_eat_ms;
	int	to_sleep_ms;
	int	must_eat_times;
	
}	t_config;

typedef struct s_philo
{
	int			id;
	t_config	*philo;
}	t_philo;


#endif