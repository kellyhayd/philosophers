/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:44:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/04 20:45:22 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	convert_nbr(char *str)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	if (str[0] == '-')
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return (nbr);
}

void	config_init(t_config *start, char **argv)
{
	start->num_philos = convert_nbr(argv[1]);
	start->to_die_ms = convert_nbr(argv[2]);
	start->to_eat_ms = convert_nbr(argv[3]);
	start->to_sleep_ms = convert_nbr(argv[4]);
	if (argv[5])
		start->must_eat_times = convert_nbr(argv[5]);
}

void	*philo_routine(void)
{

}

void	init_threads(t_config *config, t_philo *philos)
{

}

int	main(int argc, char **argv)
{
	int			i;
	t_config	config;
	t_philo		philos;
	pthread_t	*thread;

	if (argc < 5 || argc > 6)
		return (write(2, "Wrong argument count\n", 22), 1);
	i = 1;
	while (i < argc)
	{
		if (convert_nbr(argv[i]) < 0)
			return (write(2, "Arguments must be positive integers\n", 46), 1);
		i++;
	}
	config_init(&config, argv);
	// init_threads(&config, &philos);
	thread = malloc(sizeof(pthread_t) * config.num_philos);
	i = 0;
	while (i < argc)
	{
		pthread_create(thread[i], NULL, philo_routine, &config);
		pthread_join(thread[i], NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
