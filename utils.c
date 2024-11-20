#include "philo.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

bool	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long	gettime()
{
	long		time;
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1e3 + (tv.tv_usec / 1e3);
	return (time);
}

void	precise_usleep(long ms)
{
	long	start;

	start = gettime();
	while (gettime() - start < ms)
		usleep(100);
}

bool	is_dead(t_philo *philo)
{
	long	elapsed;
	long	now;
	long	last_meal;

	last_meal = philo->lm_t;
	now = gettime();
	elapsed = now - last_meal;
	if (elapsed > philo->table->tto_die)
	{
		set_bool(&philo->philo_mtx, &philo->dead, true);
		return (1);
	}
	return (0);
}