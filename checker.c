#include "philo.h"

long	ft_atol(const char *str)
{
	int	i;
	long	num;
	int	sign;
	
	i = 0;
	num = 0;
	sign = 1;
	while (str[i])
	{
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				sign = -1;
			i++;
		}
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		while (str[i] >= '0' && str[i] <= '9')
			num = (num * 10) + (str[i++] - '0');
		if (str[i] != '\0')
			break ;
	}
	return (num * sign);
}

static bool	is_positive_int(char *argv)
{
	long	num;

	num = ft_atol(argv);
	if (num <= 0 || num > INT_MAX)
		return (0);
	return (1);
}

static bool	is_unsigned_int(char *argv)
{
	long	num;

	num = ft_atol(argv);
	if (num < 0 || num > INT_MAX)
		return (0);
	return (1);
}

static bool	valid_inputs(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (i == 5 )
		{
			if (!is_unsigned_int(argv[i]))
				return (0);
		}
		else if (!is_positive_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

bool	correct_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (!valid_inputs(argv))
		return (0);
	return (1);
}
