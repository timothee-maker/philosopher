/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:36:53 by tnolent           #+#    #+#             */
/*   Updated: 2025/04/07 15:07:16 by tnolent          ###   ########.fr       */
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

void	init_philo(t_program *program, t_philo *philo,
		char **av, pthread_mutex_t forks[])
{
	int	i;

	i = 0;
	while (i < atoi(av[0]))
	{
		philo[i].last_meal = get_current_time();
		philo[i].start_time = get_current_time();
		philo[i].num_of_philos = atoi(av[0]);
		philo[i].time_to_die = atoi(av[1]);
		philo[i].time_to_eat = atoi(av[2]);
		philo[i].time_to_sleep = atoi(av[3]);
		if (av[4])
			philo[i].num_times_to_eat = atoi(av[4]);
		else
			philo[i].num_times_to_eat = -1;
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].dead = &program->dead_flag;
		philo[i].write_lock = &program->write_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_lock = &program->meal_lock;
		philo[i].variable_lock = &program->variable_lock;
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_fork(int nb_philo, t_philo philo[], pthread_mutex_t forks[])
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % nb_philo];
		i++;
	}
}

void	init_all(char **av, t_philo *philo, pthread_mutex_t *forks,
		t_program *program)
{
	init_fork(atoi(av[0]), philo, forks);
	init_philo(program, philo, av, forks);
	init_program(program, philo);
}
