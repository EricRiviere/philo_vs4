/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eriviere <eriviere@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:00:15 by eriviere          #+#    #+#             */
/*   Updated: 2024/11/06 17:41:46 by eriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


//ARGUMENTS --> ./philo 5 800 200 200 [5]
//1) is a number
//2) is an INT
//3) timestamp > 60ms

//Inline functions for performance + readability
static	inline bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
//Check for '-'/is_number/is_int
static const char	*valid_input(const char *str)
{
	const char	*number; //number as str
	int     len; //len of checked number as str

	len = 0;
	while (is_space(*str))//skip the spaces
		++str;
	if (*str == '+')//Accept one + symbol
		++str;
	else if (*str == '-')//No - symbol accepted
		error_exit("Only positive numbers accepted as params\n");
	if (!is_digit(*str))//if 1st c after + or ' ' is not digit error
		error_exit("Input is not a digit\n");
	number = str; //number starts from here
	while (is_digit(*str++)) //while is a digit increase len
		++len;
	if (len > 10) //len can't be > than 10 --> 2147483647 (INT MAX)
		error_exit("Only ints are accepted as param\n");
	return (number);
}

//Asci to long with INT_MAX control & without negative control
static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str); //Input controles
	while (is_digit(*str)) //char to long conversion
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX) //Max int validation
		error_exit("Only ints are accepted as param\n");
	return (num);
}

//Parsing & initializing data in table structure
//Timestamps are in ms so we need to convert: 
//1e3 --> 1000 // 6e4 --> 60000
void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Minimum timestamp accepted is 60ms\n");
	if(!argv[5])
		table->limit_meals = -1;
	else
		table->limit_meals = ft_atol(argv[5]);
}






