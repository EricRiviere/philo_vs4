#include "philo.h"

static void	*simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->table_mtx);
	philo->table->sim_start = gettime();
	philo->lm_t = gettime();
	pthread_mutex_unlock(&philo->table->table_mtx);
	while (1)
	{
		if (!get_bool(&philo->philo_mtx, &philo->full))
		{
			//Take forks & eat
			if (!is_dead(philo))
				take_forks(philo);
			if (!is_dead(philo))
				eat(philo);
			//Sleep
			if (!is_dead(philo))
				to_sleep(philo);
			//Think
			if (!is_dead(philo))
				think(philo);
			else
			{
				print_status(philo, "died");
				return (NULL);
			}
		}
		else 
			break ;
	}
	return (NULL);
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
	// pthread_mutex_lock(&table->table_mtx);
	// table->sim_start = gettime();
	// pthread_mutex_unlock(&table->table_mtx);
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philos[i].th_id, NULL);
		i++;
	}
}
