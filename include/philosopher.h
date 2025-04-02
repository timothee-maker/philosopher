#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
    int				id;
	int				eating;
	// int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	// int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*variable_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	variable_lock;
	t_philo			*philos;
}					t_program;

/*---LIBFT---*/
int 	ft_isdigit(int c);
int 	ft_atoi(const char *str);

/*---PARSING---*/
void	parse_arg(int ac, char **av);
void	init_philo(t_program *program, t_philo *philo, char **av, int position, pthread_mutex_t forks[]);
void	init_program(t_program *program, t_philo *philo);
void	init_fork(t_philo *philo, int nb_philo, pthread_mutex_t *forks);


/*---THREADS---*/
void	philo(char **av, int nb_philo, int times_eat);
void	*philo_routine(void *arg);
void	*monitor(void *arg);
void	eat_philo(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think_philo(t_philo *philo);
int		check_death(t_philo *philo);

/*---UTILS---*/
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
int		check_still_alive(t_philo *philo);
void	print_philo(char *message, t_philo *philo);

#endif
