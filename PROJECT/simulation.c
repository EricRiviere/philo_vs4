/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriviere <eriviere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:27:16 by eriviere          #+#    #+#             */
/*   Updated: 2024/11/06 16:32:47 by eriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo)
{
	write_status(THINKING, philo);
}

/*
   eat routine
   1)grab the forks
   2)eat: write eat, update last meal, update meals counter 
     p_usleep(time_to_sleep) && (bool full if fullfilled)
   3)release the forks
*/
static void	eat(t_philo *philo)
{
	//1)
	prot_mutex(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FORK, philo);
	prot_mutex(&philo->second_fork->fork, LOCK);
	write_status(TAKE_FORK, philo);

	//2)
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
	p_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals > 0 && philo->meals_counter == philo->table->limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);

	//3)
	prot_mutex(&philo->first_fork->fork, UNLOCK);
	prot_mutex(&philo->second_fork->fork, UNLOCK);
}

/*
	0)wait all philos, synchro start
	1)endless loop philo
*/

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	//set last meal time
	while (!simulation_finished(philo->table))
	{
		//1)Am I full?
		if (philo->full)
			break ;
		//2)eat
		eat(philo);
		//3)sleep -->write_status & precise usleep
		write_status(SLEEPING, philo);
		p_usleep(philo->table->time_to_sleep, philo->table);
		//4)think
		thinking(philo);
	}

	return (NULL);
}

/*
	Arguments: ./philo 5 800 200 200 [5]
	  argv[0] = program name
      argv[1] = philosopher number
      argv[2] = time to die
      argv[3] = time to sleep
      argv[4] = time to rest
      argv[5] = maximum meals/philospher (optional)
	Posible outcomes:
	  1)All philosophers are full
	  2)A philospher died
	-------
	0) If no meals, return ->[0]
	0.1) If only one philo -> create a function for the case
	1) Create all threads (all philosophers)
	2) Create a monitor thread -> search for dead philosophers
	3) Synchronize the beggining of the simulation
		when we use pthread_create the philo starts running
		we want every philo to start simultaneously
	4) Join every thread
*/

void	dinner_start(t_table *table)
{
	int	i;

	i = 0;
	if (table->limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		;
	else
	{
		while (i < table->philo_nbr)
		{
			prot_thread(&table->philos[i].thread_id, dinner_simulation,
					&table->philos[i], CREATE);
			i++;
		}
	}
	//Start simulation
	table->start_simulation = gettime(MILLISECOND);
	//All threads are ready
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	//Wait for every thread
	i = 0;
	while (i < table->philo_nbr)
	{
		prot_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}
