#include "philo.h"

void    *monitor(void *data)
{
    t_table *table;

    table = (t_table *)data;
    int full_philos;
    int i;
    while(1)
    {
        usleep(10);
        if (get_bool(&table->table_mtx, &table->philo_dead))
            break ;
        if (table->philo_nbr == 1)
        {
            print_dead(&table->philos[0], "died");
            break ;
        }
        full_philos = 0;
        i = 0;
        while(i < table->philo_nbr)
        {
            if(get_bool(&table->philos[i].philo_mtx, &table->philos[i].full))
                full_philos++;
            i++;
        }
        if (full_philos == table->philo_nbr)
        {
            set_bool(&table->table_mtx, &table->philo_dead, true);
            break ;
        }
    }
    return (NULL);
}