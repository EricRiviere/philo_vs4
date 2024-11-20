#include <stdio.h> //printf
#include <stdlib.h> //malloc & free
#include <unistd.h> //write, usleep
#include <stdbool.h> //booleans
#include <pthread.h> // mutex: init/destroy/lock/unclock
		  // threads: create/join/detach
#include <sys/time.h> //gettimeofday
#include <limits.h> //INT min/max limit
#include <errno.h>

//Philosophers states
typedef	enum	e_status
{
	TAKE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}	t_philo_status;

//Time codes:
typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

//Pthread enum:
typedef enum e_tcode
{
	DESTROY,
	INIT,
	LOCK,
	UNLOCK,
	CREATE,
	DETACH,
	JOIN,
}	t_tcode;
//Creation of 2 arrays 1)philosophers/threads 2)forks/mutex
//Arguments: ./philo 5 800 200 200 [5]
//	argv[0] = program name
//      argv[1] = philosopher number
//      argv[2] = time to die
//      argv[3] = time to sleep
//      argv[4] = time to rest
//      argv[5] = maximum meals/philospher (optional)

//STRUCTURES

//Table structure initializer (contains all data)
typedef	struct	s_table t_table;

//Mutex structure to shorten calls + more readable
typedef	pthread_mutex_t	t_mtx;
//Threat structure "" 
typedef	pthread_t	t_tht;

//Fork structure
typedef struct s_fork
{
	t_mtx	fork; //mutex
	int	fork_id; //fork id
}	t_fork;

//Philosopher structure
typedef struct	s_philo
{
	int	id; //Philosopher id
	long	meals_counter; //Counter to know meals/philosopher
	bool	full; //Flag to know if a philosopher is full
	long	last_meal_time; //time from last meal
	t_fork	*first_fork; //A fork is a mutex
	t_fork	*second_fork;
	t_tht	thread_id; //A philosopher is a thread
	t_mtx	philo_mutex; //To avoid race while reading from philo
	t_table	*table; //Pointer to table data structure
}	t_philo;

//Table structure definition
struct s_table
{
	long	philo_nbr; //argv[1]
	long	time_to_die; //argv[2]
	long    time_to_eat; //argv[3]
	long    time_to_sleep; //argv[4]
	long	limit_meals; //argv[5] | FLAG if -1
	long	start_simulation; //start timestamp
	bool	end_simulation; //philosopher dies OR all philosophers are full
	bool	all_threads_ready; //synchro philos
	t_mtx	table_mutex; //avoid races while reading from table
	t_mtx	write_mutex; //avoid races while writing in console
	t_fork	*forks; //pointer to fork array
	t_philo	*philos; //pointer to philosophers array
};

//FUNCTIONS:

//utils.c
void    error_exit(const char *error);
void	write_status(t_philo_status status, t_philo *philo);

//parse.c
void    parse_input(t_table *table, char **argv);

//prot_func.c
void    *prot_malloc(size_t bytes);
void	prot_mutex(t_mtx *mutex, t_tcode code);
void	prot_thread(t_tht *threat, void *(*foo)(void *), void *data, t_tcode code);

//init.c
void	data_init(t_table *table);

//getters_setters.c
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);

//synchro_utils.c:
void	wait_all_threads(t_table *table);
long	gettime(t_time_code time_code);
void	p_usleep(long usec, t_table *table);

//simulation
void	dinner_start(t_table *table);


