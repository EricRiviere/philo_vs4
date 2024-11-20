// 1st version:
// If you compile & execute many times, you'll have errors some times, the order status wont
//be allways 1000 (because order status is not locked)
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#define	WNUM 200

// Order status / shared resourse
uint64_t	order_status = 0;

// Make coffee + serve + update order status process / function to execute
void	*update_order_status(void *data)
{
	order_status += 1;
	return (NULL);
}

int	main(void)
{
	pthread_t	workers[WNUM];

	for (int i = 0; i < WNUM; i++)
	{
		if (pthread_create(workers + i, NULL, update_order_status, NULL))
			exit(EXIT_FAILURE);
	}
	for (int i = 0; i < WNUM; i++)
	{
		pthread_join(workers[i], NULL);
	}
	printf("\t%llu\n",order_status);
	return (0);
}

//2nd Version
//We'll use mutex which is a structure that allow to stop a thread to exxecude a code called
//"critical section"
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#define	WNUM 100

// Order status / shared resourse
int	order_status = 0;
//Lock
pthread_mutex_t	order_status_lock;//we can use pthread_mutex_initializer() here also

// Make coffee + serve + update order status process / function to execute
void	*update_order_status(void *data)
{
	//We need to lock
	pthread_mutex_lock(&order_status_lock);
	order_status += 1;
	sleep(10);
	//Then unlock
	pthread_mutex_unlock(&order_status_lock);
	return (NULL);
}

int	main(void)
{
	pthread_t	workers[WNUM];

	//We need to initialize the structure to use it
	pthread_mutex_init(&order_status_lock, NULL);
	for (int i = 0; i < WNUM; i++)
	{
		if (pthread_create(workers + i, NULL, update_order_status, NULL))
			exit(EXIT_FAILURE);
	}
	sleep(10);
	for (int i = 0; i < WNUM; i++)
	{
		pthread_join(workers[i], NULL);
	}
	printf("\t%d\n",order_status);
	return (0);
}

