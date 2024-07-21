/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 17:16:35 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 19:36:24 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	config.forks = malloc(sizeof(pthread_mutex_t) * config.num_philos);
	init_philo(philo, &config);
	init_fork_mutex(&config);
	start_threads(philo, &config);
	destroy_all_mutex(philo);
	free(philo);
	free(config.forks);
	return (EXIT_SUCCESS);
}
