/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:27:58 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/13 22:36:24 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

/**
 * @brief Struct that contains the arguments that define the program parameters
 *
 * @var num_philos: The number of philos and also the number of forks
 * @var to_die_ms: Time in milliseconds that if a philosopher don't
 * 		start to eat, they die;
 * @var to_eat_ms: Time in milliseconds it takes for a philosopher to eat
 * @var to_sleep_ms: Time in milliseconds a philosopher will spend sleeping
 * @var must_eat_times (optional): If all philos have eaten at least
 * 		must_eat_times, the simulation stops. If not specified,
 * 		the simulation stops when a philo dies.
 */
typedef struct s_config
{
	int				num_philos;
	int				to_die_ms;
	int				to_eat_ms;
	int				to_sleep_ms;
	int				must_eat_times;
	size_t			init_time;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
}	t_config;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	t_config		*config;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

//------------------------------------------- Utils
size_t	get_current_time(void);
int		convert_nbr(char *str);

#endif

