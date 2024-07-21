/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 14:27:58 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 14:21:17 by krocha-h         ###   ########.fr       */
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
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	*forks;
}	t_config;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	t_config		*config;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

//=========================================== Actions

void	taken_fork(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
void	died(t_philo *philo);

//=========================================== Threads

void	*philo_routine(void *args);
void	start_threads(t_philo *philos, t_config *config);
void	destroy_all_mutex(t_philo *philos);

//=========================================== Init

void	init_config(t_config *config, char **argv);
void	init_philo(t_philo *philos, t_config *config);
void	init_fork_mutex(t_config *config);

//=========================================== Utils

size_t	get_current_time(void);
int		convert_nbr(char *str);
int		get_dead_flag(t_philo *philo);
void	print_message(t_philo *philo, char *str, int id);

int		dead_loop(t_philo *philo);
void	*monitor_routine(void *args);

#endif
