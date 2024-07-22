/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:45:10 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/21 23:39:27 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_semaphores(t_config *config)
{
	sem_close(config->fork);
	sem_close(config->action);
	sem_unlink("philo_forks");
	sem_unlink("philo_action");
}

void	eating(t_philo *philo)
{
	sem_wait(philo->config->fork);
	print_message(philo, "has taken a fork", philo->id);
	sem_wait(philo->config->fork);
	print_message(philo, "has taken a fork", philo->id);
	print_message(philo, "is eating", philo->id);
	philo->last_meal = get_current_time();
	usleep(philo->config->to_eat_ms * 1000);
	sem_post(philo->config->fork);
	sem_post(philo->config->fork);
	philo->meals_eaten++;
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is thinking", philo->id);
	usleep(philo->config->to_sleep_ms * 1000);
}

void	actions(t_philo *philo)
{
	while (!philo->config->dead_flag
		&& (philo->meals_eaten < philo->config->must_eat_times))
	{
		eating(philo);
		sleeping(philo);
		print_message(philo, "is thinking", philo->id);
	}
}

void	*check_life(void *args)
{
	t_philo *philo;
	philo = (t_philo *)args;
	size_t	last_meal;

	last_meal = philo->last_meal;
	if ((get_current_time() - last_meal) >= philo->config->to_die_ms
		|| philo->config->dead_flag == 1)
		philo->config->dead_flag = 1;
	return (NULL);
}

void	philo_threads(t_philo *philo, int id)
{
	philo[id].id = id + 1;
	philo[id].meals_eaten = 0;
	philo[id].last_meal = get_current_time(); 
	pthread_create(&philo[id].thread, NULL, check_life, &philo);
	actions(philo);
	pthread_detach(philo[id].thread);
}

void	kill_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->config->num_philos)
	{
		kill(philo[i].pid, SIGINT);
		i++;
	}
}

void	create_process(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->config->num_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			philo_threads(philo, i);
		i++;
	}
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
	// init_philo(philo, &config);
	// start_threads(philo, &config);
	free(philo);
	return (EXIT_SUCCESS);
}