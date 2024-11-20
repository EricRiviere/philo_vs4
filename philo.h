/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriviere <eriviere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:53:03 by eriviere          #+#    #+#             */
/*   Updated: 2024/11/14 09:52:55 by eriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>//printf
# include <stdlib.h>// EXIT_FAILURE malloc & free
# include <unistd.h>//usleep (personalize)
# include <stdbool.h>//booleans
# include <pthread.h>//threads & mutex
# include <sys/time.h>//gettimeofday
# include <limits.h>//INT_MAX
# include <errno.h>//For mutex error
# define DEBUG_MODE 0 

//ENUMS//
typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	CREATE,
	DESTROY,
	JOIN,
}				t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}				t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}				t_philo_status;

//STRUCTURES//

//mutex
typedef pthread_mutex_t	t_mtx;

//to include t_table in philo before defining struct
typedef struct s_table	t_table;

//fork
typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

//philo
typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}				t_philo;

//table
struct	s_table
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		nbr_limit_meals;
	long		start_simulation;
	bool		end_simulation;
	bool		all_threads_ready;
	long		threads_running_num;
	pthread_t	monitor;
	t_mtx		table_mutex;
	t_mtx		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
};

//utils
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);

//parsing
void	parse_input(t_table *table, char **argv);

//safe functions
void	*safe_malloc(size_t bytes);
void	safe_mutex(t_mtx *mutex, t_opcode opcode);
void	safe_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);

//data init
void	data_init(t_table *table);

//dinner simulation
void	dinner_start(t_table *table);
void	thinking(t_philo *philo, bool pre_simulation);

//getters & setters
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);

//syncro utils
void	wait_all_threads(t_table *table);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
void	increase_long(t_mtx *mutex, long *value);
void	desynchronize_philos(t_philo *philos);

//write status
void	write_status(t_philo_status status, t_philo *philo, bool debug);

//monitor
void	*monitor_dinner(void *data);

//clean
void	clean(t_table *table);

#endif
