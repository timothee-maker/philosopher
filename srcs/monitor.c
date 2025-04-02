/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:06:32 by tnolent           #+#    #+#             */
/*   Updated: 2025/04/02 11:04:59 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_philo *philo)
{
	size_t	time_without_eating;
	int		i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		time_without_eating = get_current_time() - philo[i].last_meal;
		// printf("time without eating : %zu\n", time_without_eating);
		if (time_without_eating >= philo[i].time_to_die)
		{
			print_philo("\e[1;31mdied", &philo[i]);
			pthread_mutex_lock(philo[i].dead_lock);
			*philo[i].dead = 1;
			pthread_mutex_unlock(philo[i].dead_lock);
			return (0);
		}
		i++;
	}
	return (1);
}
