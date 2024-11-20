/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriviere <eriviere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:04:45 by eriviere          #+#    #+#             */
/*   Updated: 2024/11/11 16:05:51 by eriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_table(t_table *table)
{
	table->philos = NULL;
	table->tto_die = 0;
	table->tto_eat = 0;
	table->tto_sleep = 0;
	table->min_meals = -1;
}

static void	init_philos(t_table *table, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		table->philos[i]->table = table;
		table->philos[i]->philo_num = i + 1;
		table->philos[i]->meals = 0;
	}
}

bool	init_args(int argc, char **argv, t_table *table)
{
	int	num;
	if (!check_args(argc, argv))
		return (false);
	if (argc < 5 || argc > 6)
		return (false);
	if (argc == 6)
	{
		table->min_meals = ft_atoi(argv[5]);
		if (table->min_meals <= 0)
			return (false);
	}
	num = ft_atoi(argv[1]);
	table->tto_die = ft_atoi(argv[2]);
	table->tto_eat = ft_atoi(argv[3]);
	table->tto_sleep = ft_atoi(argv[4]);
	if (!(table->tto_die > 0 && table->tto_eat > 0 && table->tto_sleep > 0 && num > 0))
		return (false);
	table->philos = malloc(sizeof(t_philo *) * (num + 1));
	table->philos[num] = NULL;
	if (!table->philos)
		return (false);
	init_philos(table, num);
	return (true);
}
