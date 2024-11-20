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
		exit(EXIT_SUCCESS);
	}
}

/* check fork assignment:
int     i = 0;
 while (i < table.philo_nbr)
 {
 	printf("Philo %d F1_id: %d, F2_id: %d\n",
		table.philos[i].id,
		table.philos[i].first_fork->id,
		table.philos[i].second_fork->id);
	i++;
}
*/
