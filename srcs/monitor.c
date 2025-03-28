/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:06:32 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/28 13:58:37 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_philo *philo, size_t time)
{
	int		i;
	size_t	time_without_eating;
	size_t	tmp_time;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		time_without_eating = get_current_time() - philo[i].last_meal;
		printf("%zu philo : %d last meal : %zu time without eating : %zu\n", time, philo[i].id, philo[i].last_meal, time - philo[i].last_meal);
		if (time_without_eating > philo->time_to_die)
		{
			pthread_mutex_lock(philo->dead_lock);
			*philo->dead = 1;
			print_philo("died", &philo[i]);
			pthread_mutex_unlock(philo->dead_lock);
			return (0);
		}
		i++;
	}
	return (1);
}
