/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriviere <eriviere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:59:49 by eriviere          #+#    #+#             */
/*   Updated: 2024/11/06 17:52:19 by eriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int ph_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;

	if(philo->id % 2 != 0)
	{
		philo->first_fork = &forks[ph_position];
		philo->second_fork = &forks[(ph_position + 1) % (philo_nbr)];
	}
	else if (philo->id % 2 == 0)
	{
		philo->second_fork = &forks[ph_position];
		philo->first_fork = &forks[(ph_position + 1) % (philo_nbr)];
	}
}

static void	philo_init(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->full = false;
		philo->last_meal_time = 0;
		philo->table = table;
		prot_mutex(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->philos = prot_malloc(sizeof(t_philo) * table->philo_nbr);
	prot_mutex(&table->table_mutex, INIT);
	prot_mutex(&table->write_mutex, INIT);
	table->forks = prot_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		prot_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = 1;
		i++;
	}
	philo_init(table);
}
