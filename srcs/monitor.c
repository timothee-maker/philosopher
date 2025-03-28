/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:06:32 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/28 11:14:47 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	check_death(t_philo *philo, size_t time)
{
	int		i;
	size_t	times_left;
	size_t	tmp_time;

	// printf("philo id : %d\n", philo[i++].id);
	tmp_time = time;
	time =  get_current_time() - tmp_time;
	i = 0;
	while (&philo[i])
	{
		times_left = get_current_time() - philo->last_meal;
		// printf("%zu philo : %d last meal : %zu time without eating : %zu\n", time, philo->id, philo->last_meal, time - philo->last_meal);
		if (times_left > philo->time_to_die && philo->last_meal != 0)
		{
			pthread_mutex_lock(philo->dead_lock);
			*philo->dead = 1;
			printf("%zu %d died\n", time, philo->id);
			pthread_mutex_unlock(philo->dead_lock);
			return (0);
		}
		i++;
	}
	return (1);
}
