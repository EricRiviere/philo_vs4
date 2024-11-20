#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
//Macros
# define ARGS_ERROR "Incorrect arguments.\n\n"\
			"Time to must be positive int != 0.\n"\
			"Program execution example:\n"\
			"./philo philos ttd tte tts [meals]"


//Shortener
typedef pthread_mutex_t	t_mtx;

//Predefs
typedef struct	s_philo t_philo;
typedef struct	s_table t_table;
typedef struct	s_fork t_fork;

//Structs
struct	s_fork
{
	t_mtx	fork;
	int	id;
};

struct	s_philo
{
	int		id;
	long		meals;
	long		lm_t;
	bool		full;
	pthread_t	th_id;
	t_mtx		philo_mtx;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_table		*table;
};

struct	s_table
{
	long	philo_nbr;
	long	tto_die;
	long	tto_eat;
	long	tto_sleep;
	long	min_meals;
	long	sim_start;
	bool	all_thr_ready;
	t_mtx	table_mtx;
	t_mtx	print_mtx;
	t_fork	*forks;
	t_philo	*philos;
	
};

//Utils
void	error_exit(const char *error);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
long	gettime();
bool    get_long(t_mtx *mutex, long *value);
void    set_long(t_mtx *mutex, long *dest, long value);
void	precise_usleep(long ms);
void	wait_all_threads(t_table *table);

//Check inputs
bool	correct_input(int argc, char **argv);
long	ft_atol(const char *str);

//Init data
void	init_data(t_table *table, char **argv);

//Simulation
void	start_simulation(t_table *table);

//Print status
void	print_status(t_philo *philo, const char *status);
#endif
