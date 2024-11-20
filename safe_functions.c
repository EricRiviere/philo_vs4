/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriviere <eriviere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:31:49 by eriviere          #+#    #+#             */
/*   Updated: 2024/11/14 09:25:53 by eriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Protected malloc function
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Error with malloc");
	return (ret);
}

//Mutex error function
static void	error_mutex(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK
			|| opcode == DESTROY))
		error_exit("The value specified by mutex is invalid.");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid.");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if blocked waiting for mutex.");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (status == ENOMEM)
		error_exit("The process cannot allocate memory for another mutex.");
	else if (status == EBUSY)
		error_exit("Mutex is locked.");
}

//Protected Mutex function with mutex error returns
void	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		error_mutex(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		error_mutex(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		error_mutex(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		error_mutex(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong mutex tcode\n");
}

//Thread error function
static	void	error_thread(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No necessary resources to create another thread.");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permission");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("The value specified by attr is invalid.");
	else if (status == EINVAL)
		error_exit("The value specified by thread is not joinable.");
	else if (status == ESRCH)
		error_exit("No thread found with the given thread ID.");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected.");
}

void	safe_thread(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		error_thread(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		error_thread(pthread_join(*thread, NULL), opcode);
	else
		error_exit("Wrong thread code");
}
