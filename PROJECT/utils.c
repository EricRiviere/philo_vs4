/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriviere <eriviere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:00:35 by eriviere          #+#    #+#             */
/*   Updated: 2024/11/06 16:29:37 by eriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

/*
   Cronometer for simulation
   time_code--> SECONDS MILLISECONDS MICROSECONDS
   in timeval struct, tv refers to TimeValue
*/
long	gettime(t_time_code time_code)
{
	struct timeval	tv;
	if (gettimeofday(&tv, NULL) == -1)
		error_exit("Gettimeofday failed.");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));//1 seg + (microsegundos / 1 segundo(0,0000001)
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3 ) + (tv.tv_usec / 1e3));// seconds to mls + mcs to mls
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6 ) + tv.tv_usec);// seconds to mcs + mcs
	else
		error_exit("Wrong time code for gettime function.");
	return (1111);
}

/*
   Precise usleep
	Is the simulation finished?
	1)usleep the majority of time
	2)refine last microsec with spinlock
*/
void	p_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		//1)
		if (simulation_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;

		// to get a spinlock threshold
		if (rem > 1e3)
			usleep(rem/2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->table->start_simulation;

	if (philo->full)
		return ;

	prot_mutex(&philo->table->write_mutex, LOCK);
	if((status == TAKE_FORK)
			&& !simulation_finished(philo->table))
		printf("%ld --> %d has taken a fork\n", elapsed, philo->id);
	else if((status == EATING)
			&& !simulation_finished(philo->table))
		printf("%ld --> %d is eating\n", elapsed, philo->id);
	else if((status == SLEEPING)
			&& !simulation_finished(philo->table))
		printf("%ld --> %d is sleeping\n", elapsed, philo->id);
	else if((status == THINKING)
			&& !simulation_finished(philo->table))
		printf("%ld --> %d is thinking\n", elapsed, philo->id);
	else if((status == DIED)
			&& !simulation_finished(philo->table))
		printf("%ld --> %d died\n", elapsed, philo->id);
}
