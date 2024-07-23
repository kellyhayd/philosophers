/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:45:10 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/23 00:16:04 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_life(t_philo *philo)
{
	int	i;
	int	child_status;
	
	create_process(philo);
	child_status = 0;
	waitpid(-1, &child_status, 0);
	kill_process(philo);
	destroy_semaphores(philo->config);
	return (1);
}

int	main(int argc, char **argv)
{
	int				i;
	t_config		config;
	t_philo			*philo;
	pthread_t		*thread;

	if (argc < 5 || argc > 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	i = 1;
	while (i < argc)
	{
		if (convert_nbr(argv[i]) < 0)
			return (EXIT_FAILURE);
		i++;
	}
	config_init(&config, argv);
	if (!semaphores_init(&config))
		return (EXIT_FAILURE);
	philo = malloc(sizeof(t_philo) * config.num_philos);
	philo_init(philo, &config);
	philo_life(philo);
	free(philo);
	return (EXIT_SUCCESS);
}