#include "philo.h"

void    take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second_fork->fork);
	print_status(philo, "has taken a fork");
}

void    eat(t_philo *philo)
{
	philo->meals++;
    if (philo->meals == philo->table->min_meals)
        set_bool(&philo->philo_mtx, &philo->full, true);
    set_long(&philo->philo_mtx, &philo->lm_t, gettime());
	print_status(philo, "is eating");
	precise_usleep(philo->table->tto_eat);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

void    to_sleep(t_philo *philo)
{
    print_status(philo, "is sleeping");
	precise_usleep(philo->table->tto_sleep);
}

void    think(t_philo *philo)
{
    print_status(philo, "is thinking");
	precise_usleep(5);
}
