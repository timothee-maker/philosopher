/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:36:53 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/28 10:40:01 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_program(t_program *program, t_philo *philo)
{
	program->philos = philo;
	program->dead_flag = 0;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}

void	init_philo(t_program *program, t_philo *philo, int nb_philo, int die, int eat, int sleep, int position, pthread_mutex_t forks[])
{
	// program->dead_flag = 0;
	philo->last_meal = 0;
	philo->num_of_philos = nb_philo;
	philo->time_to_die = die;
	philo->time_to_eat = eat;
	philo->time_to_sleep = sleep;
	philo->id = position + 1;
	philo->dead = &program->dead_flag;
	philo->write_lock = &program->write_lock;
	philo->dead_lock = &program->dead_lock;
	philo->meal_lock = &program->meal_lock;
	pthread_mutex_init(&forks[position], NULL);
	// pthread_mutex_init(&program->write_lock, NULL);
	// pthread_mutex_init(&program->dead_lock, NULL);
	// pthread_mutex_init(&program->meal_lock, NULL);
	philo[position].meal_lock = &program->meal_lock;
	philo[position].dead_lock = &program->dead_lock;
	philo[position].write_lock = &program->write_lock;
	philo[position].l_fork = &forks[position];
	philo[position].r_fork = &forks[(position + 1) % nb_philo];
}
