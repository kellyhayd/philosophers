/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:57:16 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 18:09:45 by krocha-h         ###   ########.fr       */
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

typedef struct s_config
{
	int			num_philos;
	int			to_die_ms;
	int			to_eat_ms;
	int			to_sleep_ms;
	int			must_eat_times;
	size_t		init_time;
	int			dead_flag;
}	t_config;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	size_t		last_meal;
	t_config	*config;
}	t_philo;

#endif