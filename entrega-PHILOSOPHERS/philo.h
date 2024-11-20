/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriviere <eriviere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:06:20 by eriviere          #+#    #+#             */
/*   Updated: 2024/11/11 15:46:46 by eriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct	s_philo t_philo;

typedef struct	s_table
{
	t_philo	**philos;
	long long	tto_die;
	int			tto_eat;
	int			tto_sleep;
	int			min_meals;
}	t_table;

typedef struct s_philo
{
	t_table		*table;
	pthread_t	philo_thd;
	int			philo_num;
	int				meals;
}	t_philo;

//Check arguments:
int	ft_atoi(const char *s);
bool	check_args(int argc, char **argv);

//Init table & philosophers
void	init_table(t_table *table);
bool	init_args(int argc, char **argv, t_table *table);

#endif
