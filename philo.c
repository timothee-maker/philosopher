/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:32:19 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/24 12:45:15 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_routine(void *arg);
void	*monitor(void *arg);
void	philo(int nb_philo, int die, int eat, int sleep);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	init_philo(t_program *program, t_philo *philo, int nb_philo,  int die, int eat, int sleep, int position);
void	init_mutex(t_philo *philo, pthread_mutex_t forks[], t_program *program);
void	eat_philo(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think_philo(t_philo *philo);


int	main(int ac, char **av)
{
	// printf("%zu\n", get_current_time());
	parse_arg(ac, av);
	philo(atoi(av[1]), atoi(av[2]), atoi(av[3]), atoi(av[4]));
}

void	philo(int nb_philo, int die, int eat, int sleep)
{
	int				i;
	t_philo 		philo[nb_philo + 1];
	t_program		program;
	pthread_mutex_t forks[nb_philo];

	i = 0;
	// while (i < nb_philo)
	    // pthread_mutex_init(&forks[i++], NULL);
	init_mutex(philo, forks, &program);
	i = 0;
	while (i < nb_philo)
	{
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % nb_philo];
		i++;
	}
	program.philos = philo;
	i = 0;
	while (i < nb_philo)
	{
		init_philo(&program, &philo[i], nb_philo, die, eat, sleep, i);
		
		pthread_create(&program.philos[i].thread, NULL, philo_routine, &program.philos[i]);
		i++;
	}
	// usleep(1000000);
	// program.dead_flag = 1;
	printf("tous le monde est mort\n");
	pthread_create(&program.philos[i].thread, NULL, monitor, &program);
	i = 0;
	while (i < nb_philo + 1)
		pthread_join(philo[i++].thread, NULL);
}

void	init_mutex(t_philo *philo, pthread_mutex_t forks[], t_program *program)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		philo[i].meal_lock = &program->meal_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].write_lock = &program->write_lock;
		// pthread_mutex_init(philo[i].meal_lock, NULL);
		// pthread_mutex_init(philo[i].dead_lock, NULL);
		pthread_mutex_init(philo[i].write_lock, NULL);
		i++;
	}
}

void	init_philo(t_program *program, t_philo *philo, int nb_philo, int die, int eat, int sleep, int position)
{
	philo->num_of_philos = nb_philo;
	philo->time_to_die = die;
	philo->time_to_eat = eat;
	philo->time_to_sleep = sleep;
	philo->id = position;
	program->dead_flag = 0;
	philo->dead = &program->dead_flag;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		printf("dead flag = %d\n", *philo->dead);
		if (*philo->dead == 1)
			break;
		eat_philo(philo);
		// sleep_philo(philo);
		// think_philo(philo);
		// printf("Le philo %d vous dit bonjour\n", philo->id);
	}
	return (arg);
}

void	think_philo(t_philo *philo)
{
	// pthread_mutex_lock(philo->write_lock);
	printf("%d is thinking\n", philo->id);
	// pthread_mutex_unlock(philo->write_lock);
}

void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%d is sleeping\n", philo->id);
	ft_usleep(philo->time_to_sleep);
	pthread_mutex_unlock(philo->write_lock);
}

void	eat_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	printf("%d as taken a fork\n", philo->id);
	pthread_mutex_lock(philo->l_fork);
	printf("%d as taken a fork\n", philo->id);
	// pthread_mutex_lock(philo->meal_lock);
	printf("%d is eating\n", philo->id);
	// pthread_mutex_lock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*monitor(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	return (arg);
}

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
