/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:36:53 by tnolent           #+#    #+#             */
/*   Updated: 2025/04/02 11:19:47 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_program(t_program *program, t_philo *philo)
{
	program->philos = philo;
	// philo[0].start_time = get_current_time();
	program->dead_flag = 0;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	// pthread_mutex_init(&program->variable_lock, NULL);
}

void	init_philo(t_program *program, t_philo *philo, char **av, int position, pthread_mutex_t forks[])
{
	philo->last_meal = get_current_time();
    philo->start_time = get_current_time();
	philo->num_of_philos = atoi(av[0]);
	philo->time_to_die = atoi(av[1]);
	philo->time_to_eat = atoi(av[2]);
	philo->time_to_sleep = atoi(av[3]);
	philo->id = position + 1;
	philo->dead = &program->dead_flag;
	philo->write_lock = &program->write_lock;
	philo->dead_lock = &program->dead_lock;
	philo->meal_lock = &program->meal_lock;
	philo->variable_lock = &program->variable_lock;
	pthread_mutex_init(&forks[position], NULL);
	philo[position].meal_lock = &program->meal_lock;
	philo[position].dead_lock = &program->dead_lock;
	philo[position].write_lock = &program->write_lock;
	philo[position].l_fork = &forks[position];
	philo[position].r_fork = &forks[(position + 1) % atoi(av[1])];
}
