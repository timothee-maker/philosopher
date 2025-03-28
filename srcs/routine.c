/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:36:10 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/28 13:25:04 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	think_philo(t_philo *philo, size_t time)
{
	time = get_current_time() - time;
	// printf("%zu %d is thinking\n", time, philo->id);
    print_philo("is thinking", philo);
}

void	sleep_philo(t_philo *philo, size_t time)
{
	time = get_current_time() - time;
	// printf("%zu %d is sleeping\n", time, philo->id);
    print_philo("is sleeping", philo);
	ft_usleep(philo->time_to_sleep);
}

void	eat_philo(t_philo *philo, size_t time)
{
	// size_t	tmp_time;
	// size_t	times_left;

    // tmp_time = time;
	// time = get_current_time() - tmp_time;
	pthread_mutex_lock(philo->r_fork);
	// printf("%zu %d has taken a fork\n", time, philo->id);
    print_philo("has taken a fork", philo);
	pthread_mutex_lock(philo->l_fork);
	// time = get_current_time() - tmp_time;
	// printf("%zu %d has taken a fork\n", time, philo->id);
    print_philo("has taken a fork", philo);
	// pthread_mutex_lock(philo->meal_lock);

	// printf("%zu %d is eating\n", time, philo->id);
    print_philo("is eating", philo);
	philo->last_meal = get_current_time();
	// pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
