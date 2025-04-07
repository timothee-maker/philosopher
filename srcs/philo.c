/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:32:19 by tnolent           #+#    #+#             */
/*   Updated: 2025/04/07 15:02:06 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	parse_arg(ac, av);
	philo(&av[1]);
}

void	philo(char **av)
{
	int				i;
	t_philo			philo[200];
	pthread_mutex_t	forks[200];
	pthread_t		observor;
	t_program		program;

	init_all(av, philo, forks, &program);
	pthread_create(&observor, NULL, monitor, program.philos);
	i = 0;
	while (i < atoi(av[0]))
	{
		pthread_create(&program.philos[i].thread, NULL,
			philo_routine, &program.philos[i]);
		i++;
	}
	i = 0;
	while (i < atoi(av[0]))
		pthread_join(philo[i++].thread, NULL);
	pthread_join(observor, NULL);
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (!check_death(philo))
			break ;
		if (!check_all_ate(philo))
			break ;
		usleep(1);
	}
	return (arg);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_still_alive(philo))
	{
		if (philo->id % 2 == 0)
			eat_philo_odd(philo);
		else
			eat_philo_even(philo);
		sleep_philo(philo);
		think_philo(philo);
	}
	return (arg);
}
