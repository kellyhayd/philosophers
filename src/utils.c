/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:43:47 by krocha-h          #+#    #+#             */
/*   Updated: 2024/07/13 22:19:36 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	convert_nbr(char *str)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	if (str[0] == '-')
		return (write(2, "Arguments must be positive integers\n", 36), -1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (write(2, "Arguments must be integers\n", 27), -1);
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return (nbr);
}