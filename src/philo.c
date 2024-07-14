/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:44:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/13 22:57:32 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	init_thread(philo, &config);
	return (EXIT_SUCCESS);
}
