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
		if (get_bool(&philo->table->table_mtx, &philo->table->philo_dead))
			break ;
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
			else if (get_bool(&philo->philo_mtx, &philo->dead))
			{
				set_bool(&philo->table->table_mtx, &philo->table->philo_dead, true);
				print_dead(philo, "died");
				return (NULL);
			}
		}
		else 
			break ;
	}
	return (NULL);
}

static void	*lone_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->table_mtx);
	philo->table->sim_start = gettime();
	philo->lm_t = gettime();
	pthread_mutex_unlock(&philo->table->table_mtx);
	print_status(philo, "has taken a fork");
	if (!get_bool(&philo->philo_mtx, &philo->dead))
		precise_usleep(philo->table->tto_die);
	set_bool(&philo->philo_mtx, &philo->dead, true);
	return (NULL);
}

void	start_simulation(t_table *table)
{
	pthread_t	monitor_th;
	int	i;

	if (table->min_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
	{
		pthread_create(&table->philos[0].th_id, NULL, lone_simulation, &table->philos[0]);
		usleep(40000);
		pthread_join(table->philos[0].th_id, NULL);
	}
	else
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			pthread_create(&table->philos[i].th_id, NULL, simulation, &table->philos[i]);
			i++;
		}
	}
	pthread_create(&monitor_th, NULL, monitor, table);
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philos[i].th_id, NULL);
		i++;
	}
	pthread_join(monitor_th, NULL);
}
