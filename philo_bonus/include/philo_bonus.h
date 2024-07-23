/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:57:16 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/22 23:44:43 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_config
{
	int			num_philos;
	int			to_die_ms;
	int			to_eat_ms;
	int			to_sleep_ms;
	int			must_eat_times;
	size_t		init_time;
	int			dead_flag;
	sem_t		*fork;
	sem_t		*action;
}	t_config;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	int			pid;
	size_t		last_meal;
	t_config	*config;
	pthread_t	thread;
}	t_philo;

size_t	get_current_time(void);
void	print_message(t_philo *philo, char *str, int id);
int		convert_nbr(char *str);
void	actions(t_philo *philo);
void	kill_process(t_philo *philo);
void	create_process(t_philo *philo);
void	destroy_semaphores(t_config *config);
void	config_init(t_config *config, char **argv);
int		semaphores_init(t_config *config);
void	philo_init(t_philo *philo, t_config *config);

#endif