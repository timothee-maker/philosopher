#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

# define NORMAL "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"

typedef struct s_counter
{
	pthread_mutex_t		count_mutex;
	unsigned int		count;
}						t_counter;

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
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

int 	ft_isdigit(int c);
int 	ft_atoi(const char *str);
void	parse_arg(int ac, char **av);

#endif
