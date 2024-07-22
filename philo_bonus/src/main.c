/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:45:10 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 23:51:59 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_threads(t_philo *philo, int id)
{
	philo[id].id = id + 1;
	philo[id].meals_eaten = 0;
	philo[id].last_meal = get_current_time(); 
	pthread_create(&philo[id].thread, NULL, check_life, &philo);
	actions(philo);
	pthread_detach(philo[id].thread);
}

int	philo_life(t_philo *philo)
{
	int	i;
	
	i = 0;
	create_process(philo);
	while (i < philo->config->num_philos)
	{
		waitpid(philo[i].pid, 0, 0);
		i++;
	}
	kill_process(philo);
	destroy_semaphores(philo->config);
	return (1);
}

int	semaphores_init(t_config *config)
{
	sem_unlink("philo_fork");
	sem_unlink("philo_action");
	config->fork = sem_open("philo_fork", O_CREAT, 0700, config->num_philos);
	config->action = sem_open("philo_action", O_CREAT, 0700, 1);
	if (config->fork == SEM_FAILED || config->action == SEM_FAILED)
	{
		destroy_semaphores(config);
		return (0);
	}
	return (1);
}

void	config_init(t_config *config, char **argv)
{
	config->num_philos = convert_nbr(argv[1]);
	config->to_die_ms = convert_nbr(argv[2]);
	config->to_eat_ms = convert_nbr(argv[3]);
	config->to_sleep_ms = convert_nbr(argv[4]);
	if (argv[5])
		config->must_eat_times = convert_nbr(argv[5]);
	else
		config->must_eat_times = -1;
	config->init_time = get_current_time();
	config->dead_flag = 0;
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
	philo_life(philo);
	free(philo);
	return (EXIT_SUCCESS);
}