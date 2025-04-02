/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:36:10 by tnolent           #+#    #+#             */
/*   Updated: 2025/04/02 11:05:37 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	think_philo(t_philo *philo)
{
    print_philo("\e[1;34mis thinking", philo);
}

void	sleep_philo(t_philo *philo)
{
    print_philo("\e[1;32mis sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

void	eat_philo(t_philo *philo)
{
	static int	i = 1;

	if (philo->id % 2 == 0 && i == 1)
	{
		ft_usleep(10);
		i = 0;
	}
	pthread_mutex_lock(philo->r_fork);
    print_philo("\x1B[1;35mhas taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
    print_philo("\x1B[1;35mhas taken a fork", philo);
	// printf("time without eating : %zu\n", time_without_eating);
	pthread_mutex_lock(philo->meal_lock);
	print_philo("\e[1;33mis eating", philo);
	
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	check_still_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}
