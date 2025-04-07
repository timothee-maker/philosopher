/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:38:32 by tnolent           #+#    #+#             */
/*   Updated: 2025/04/03 12:08:01 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_philo(char *message, t_philo *philo)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	if (!check_still_alive(philo))
	{
		pthread_mutex_lock(philo->write_lock);
		printf("%zu %d %s\e[0m\n", time, philo->id, message);
		pthread_mutex_unlock(philo->write_lock);
	}
}
