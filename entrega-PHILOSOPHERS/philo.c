/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriviere <eriviere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:03:32 by eriviere          #+#    #+#             */
/*   Updated: 2024/11/11 16:13:20 by eriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	main(int argc, char **argv)
{
	t_table	table;
	init_table(&table);
	if (!init_args(argc, argv, &table))
			printf("Invalid arguments\n");
	/*
	if (argc >= 5 && argc <= 6)
	{
		if (check_args(argc, argv))
		{
			t_table	table;
			init_table(&table);
			init_args(argc, argv, table);
		}
		else
			printf("Arguments KO\n");
	}
	*/
	else
		printf("Arguments KO\n");
	return (0);
}

