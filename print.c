#include "philo.h"

void	print_status(t_philo *philo, const char *status)
{
	long	elapsed;

	elapsed = gettime() - philo->table->sim_start;
	pthread_mutex_lock(&philo->table->print_mtx);
	printf("%-6ld %d %s\n", elapsed, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_mtx);
}
