/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:44:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/13 22:47:37 by krocha-h         ###   ########.fr       */
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
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % config->num_philos];
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

void	*philo_routine(void*)
{
	// pthread_mutex_lock(&mutex);
	write(1, "thread working!\n", 16);
	usleep(3);
	// pthread_mutex_unlock(&mutex);
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
	i = 0;
	while (i < config.num_philos)
	{
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < config.num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
