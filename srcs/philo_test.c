/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:32:19 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/26 15:13:57 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*philo_routine(void *arg);
void	*monitor(void *arg);
void	philo(int nb_philo, int die, int eat, int sleep, int times_eat);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	init_philo(t_program *program, t_philo *philo, int nb_philo, int die, int eat, int sleep, int position, pthread_mutex_t forks[]);
void	init_program(t_program *program, t_philo *philo);
void	init_mutex(t_philo *philo, pthread_mutex_t forks[], t_program *program);
void	eat_philo(t_philo *philo, size_t time);
void	sleep_philo(t_philo *philo, size_t time);
void	think_philo(t_philo *philo, size_t time);
void	check_death(t_philo *philo);


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
	pthread_create(&observor, NULL, monitor, &program.philos);
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

void	init_program(t_program *program, t_philo *philo)
{
	program->dead_flag = 0;
	program->philos = philo;
	philo->dead = &program->dead_flag;
	philo->write_lock = &program->write_lock;
	philo->dead_lock = &program->dead_lock;
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
void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// *philo->dead = 0;
	int i = 0;
	printf("%s num of philos %d %s\n", GREEN, philo[0].num_of_philos, NORMAL);
	// while (i < philo[0].num_of_philos)
	// while (1)
	// {
	// 	if (*philo->dead == 1)
	// 	{
	// 		printf("coucou\n");
	// 		break;
	// 	}
	// 	check_death(philo);
	// }
	return (arg);
}

// void	check_death(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (&philo[i])
// 	{
// 		printf("philo id : %d\n", philo[i++].id);
// 	}
// 	exit (0);
// }

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	size_t 	time;

	time = get_current_time();
	philo = (t_philo *)arg;
	philo->start_time = get_current_time();
	printf("%s num of philos %d %s\n", GREEN, philo[0].num_of_philos, NORMAL);
	while (1)
	{
		printf("dead flag = %d\n", *philo->dead);
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

void	think_philo(t_philo *philo, size_t time)
{
	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - time;
	printf("%zu %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}

void	sleep_philo(t_philo *philo, size_t time)
{
	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - time;
	printf("%zu %d is sleeping\n", time, philo->id);
	ft_usleep(philo->time_to_sleep);
	pthread_mutex_unlock(philo->write_lock);
}

void	eat_philo(t_philo *philo, size_t time)
{
	size_t	tmp_time;
	size_t	times_left;

	times_left = get_current_time() - philo->last_meal;
	tmp_time = time;
	time = get_current_time() - tmp_time;
	printf("%zu philo : %d last meal : %zu time without eating : %zu\n", time, philo->id, philo->last_meal, time - philo->last_meal);
	if (times_left > philo->time_to_die && philo->last_meal != 0)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		printf("%zu %d died\n", time, philo->id);
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	time = get_current_time() - tmp_time;
	printf("%zu %d has taken a fork\n", time, philo->id);
	pthread_mutex_lock(philo->l_fork);
	time = get_current_time() - tmp_time;
	printf("%zu %d has taken a fork\n", time, philo->id);
	// pthread_mutex_lock(philo->meal_lock);

	printf("%zu %d is eating\n",time, philo->id);
	philo->last_meal = time;
	// pthread_mutex_lock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
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
