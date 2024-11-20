#include "philo.h"

static void	*simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
//	wait_all_threads(philo->table);
//	philo->table->sim_start = gettime();
	while (1)
	{
		//Take forks & eat
		pthread_mutex_lock(&philo->first_fork->fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->second_fork->fork);
		print_status(philo, "has taken a fork");
		philo->meals++;
		print_status(philo, "is eating");
		precise_usleep(philo->table->tto_eat);
		pthread_mutex_unlock(&philo->first_fork->fork);
		pthread_mutex_unlock(&philo->second_fork->fork);
		//Sleep
		print_status(philo, "is sleeping");
		precise_usleep(philo->table->tto_sleep);
		//Think
		print_status(philo, "is thinking");
	}
}

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philos[i].th_id, NULL, simulation, &table->philos[i]);
		i++;
	}
	table->sim_start = gettime();
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philos[i].th_id, NULL);
		i++;
	}
}
