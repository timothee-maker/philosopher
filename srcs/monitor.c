/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:06:32 by tnolent           #+#    #+#             */
/*   Updated: 2025/04/07 15:11:58 by tnolent          ###   ########.fr       */
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
		pthread_mutex_lock(philo[i].meal_lock);
		time_without_eating = get_current_time() - philo[i].last_meal;
		pthread_mutex_unlock(philo[i].meal_lock);
		if (time_without_eating >= philo[i].time_to_die)
		{
			print_philo("died", &philo[i]);
			pthread_mutex_lock(philo[i].dead_lock);
			*philo[i].dead = 1;
			pthread_mutex_unlock(philo[i].dead_lock);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_all_ate(t_philo *philo)
{
	int		i;
	int		philo_who_ate_all;

	i = 0;
	philo_who_ate_all = 0;
	if (philo[0].num_times_to_eat == -1)
		return (1);
	while (i < philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_eaten >= philo[i].num_times_to_eat)
			philo_who_ate_all++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (philo_who_ate_all == philo[0].num_of_philos)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
	return (1);
}
