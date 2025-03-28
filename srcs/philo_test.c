/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:32:19 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/28 11:17:05 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	int	times_eat;
	// printf("%zu\n", get_current_time());
	times_eat = 0;
	parse_arg(ac, av);
	if (av[5])
		times_eat = atoi(av[5]);
	philo(atoi(av[1]), atoi(av[2]), atoi(av[3]), atoi(av[4]), times_eat);
}

void	philo(int nb_philo, int die, int eat, int sleep, int times_eat)
{
	int				i;
	t_philo 		philo[nb_philo + 1];
	pthread_mutex_t forks[nb_philo];
	pthread_t		observor;
	t_program		program;

	i = 0;
	while (i < nb_philo)
	{
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % nb_philo];
		i++;
	}
	init_program(&program, philo);
	pthread_create(&observor, NULL, monitor, program.philos);
	i = 0;
	// printf("%s caca%s\n", GREEN, NORMAL);
	while (i < nb_philo)
	{
		init_philo(&program, &philo[i], nb_philo, die, eat, sleep, i, forks);
		pthread_create(&program.philos[i].thread, NULL, philo_routine, &program.philos[i]);
		i++;
	}
	i = 0;
	while (i < nb_philo)
		pthread_join(philo[i++].thread, NULL);
	pthread_join(observor, NULL);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	size_t	time;

	philo = (t_philo *)arg;
	time = get_current_time();
	// printf("%s num of philos %d %s\n", GREEN, philo[0].num_of_philos, NORMAL);
	while (1)
	{
		if (check_death(philo, time))
		{
			printf("monitor is cut\n");
			break;
		}
	}
	return (arg);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	size_t 	time;

	time = get_current_time();
	philo = (t_philo *)arg;
	philo->start_time = get_current_time();
	while (1)
	{
		// printf("dead flag = %d\n", *philo->dead);
		if (*philo->dead == 1)
			break;
		eat_philo(philo, time);
		if (*philo->dead == 1)
			break;
		sleep_philo(philo, time);
		think_philo(philo, time);
	}
	return (arg);
}
