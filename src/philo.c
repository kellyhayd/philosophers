/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:44:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/14 14:27:36 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	size_t	time_now;
	
	time_now = get_current_time() - philo->config->init_time;
	printf("%u %d is thinking\n", time_now, philo->id);
}

void	sleeping(t_philo *philo)
{
	size_t	time_now;
	
	time_now = get_current_time() - philo->config->init_time;
	printf("%u %d is sleeping\n", time_now, philo->id);
	usleep(philo->config->to_sleep_ms * 1000);
}

void	eating(t_philo *philo)
{
	size_t	time_now;
	
	time_now = get_current_time() - philo->config->init_time;
	printf("%u %d is eating\n", time_now, philo->id);
	usleep(philo->config->to_eat_ms * 1000);
}

void	print_taken_fork(t_philo *philo)
{
	size_t	time_now;
	
	time_now = get_current_time() - philo->config->init_time;
	printf("%u %d has taken a fork\n", time_now, philo->id);
}

void	*philo_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(philo->l_fork);
	print_taken_fork(philo);
	pthread_mutex_lock(philo->r_fork);
	print_taken_fork(philo);
	eating(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	sleeping(philo);
	thinking(philo);
}
void	start_threads(t_philo *philos, t_config *config)
{
	int	i;
	
	i = 0;
	while (i < config->num_philos)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < config->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int				i;
	t_config		config;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*forks;

	if (argc < 5 || argc > 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	i = 1;
	while (i < argc)
	{
		if (convert_nbr(argv[i]) < 0)
			return (EXIT_FAILURE);
		i++;
	}
	init_config(&config, argv);
	philo = malloc(sizeof(t_philo) * config.num_philos);
	forks = malloc(sizeof(pthread_mutex_t) * config.num_philos);
	init_philo(philo, &config, forks);
	i = 0;
	while (i < config.num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	start_threads(philo, &config);
	return (EXIT_SUCCESS);
}
