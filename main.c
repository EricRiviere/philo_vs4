#include "philo.h"

int	main(int argc, char **argv)
{	
	t_table	table;

	if (!correct_input(argc, argv))
		error_exit(ARGS_ERROR);
	else
	{
		init_data(&table, argv);
		start_simulation(&table);
		cleanup_table(&table);
		exit(EXIT_SUCCESS);
	}
}
