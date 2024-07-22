/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:45:10 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/22 08:43:33 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_threads(t_philo *philo, int id)
{
	pthread_create(&philo[id].thread, NULL, check_life, &philo);
	actions(philo);
	pthread_detach(philo[id].thread);
}

int	philo_life(t_philo *philo)
{
	int	i;
	
	i = 0;
	printf("entrando em philo_life\n");
	create_process(philo);
	printf("process created\n");
	while (i < philo->config->num_philos)
	{
		waitpid(philo[i].pid, 0, 0);
		i++;
	}
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
	printf("config init ok\n");
	if (!semaphores_init(&config))
		return (EXIT_FAILURE);
	printf("semaphores init ok \n");
	philo = malloc(sizeof(t_philo) * config.num_philos);
	philo_init(philo, &config);
	printf("philo init ok\n");
	philo_life(philo);
	free(philo);
	return (EXIT_SUCCESS);
}