/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriviere <eriviere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:41:16 by eriviere          #+#    #+#             */
/*   Updated: 2024/11/06 16:38:26 by eriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
   To avoid writing LOOK/UNLOCK everywhere
*/

//BOOL
bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	prot_mutex(mutex, LOCK);
	ret = *value;
	prot_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	prot_mutex(mutex, LOCK);
	*dest = value;
	prot_mutex(mutex, UNLOCK);
}

//LONGS
long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	prot_mutex(mutex, LOCK);
	ret = *value;
	prot_mutex(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	prot_mutex(mutex, LOCK);
	*dest = value;
	prot_mutex(mutex, UNLOCK);
}

//Special for readability
bool	simulation_finished(t_table *table)
{
	bool	ret;

	ret = get_bool(&table->table_mutex, &table->end_simulation);
	return (ret);
}
