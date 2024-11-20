//*PTHREAD library prototypes:

//int   pthread_create(pthread_t *, const pthread_attr_t *, void *(*)(void *), void *);
	//https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_create.html
	//(pointer to thread, pointer to thread attribute, function, pointer to data)

//int   pthread_join(pthread_t, void **);
	//https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_join.html
	//(thread, pointer value)


// 1st version
/*
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*make_coffee(void *data)
{
	printf("Worker preparing coffee\n");
	sleep(20);
	printf("Coffe ready!\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	starbucks_worker_1;
	pthread_t	starbucks_worker_2;

	pthread_create(&starbucks_worker_1, NULL, make_coffee, NULL);
	pthread_create(&starbucks_worker_2, NULL, make_coffee, NULL);
	sleep(5);

	return (0);
}
*/

//Second Version (pthread_join())
/*
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*make_coffee(void *data)
{
	printf("Worker preparing coffee\n");
	sleep(20);
	printf("Coffe ready!\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	starbucks_worker_1;
	pthread_t	starbucks_worker_2;

	pthread_create(&starbucks_worker_1, NULL, make_coffee, NULL);
	pthread_create(&starbucks_worker_2, NULL, make_coffee, NULL);
	pthread_join(starbucks_worker_1, NULL);
	pthread_join(starbucks_worker_2, NULL);

	return (0);
}
*/

//3rd Version (multiple workers)
/*
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*make_coffee(void *data)
{
	printf("Worker preparing coffee\n");
	sleep(20);
	printf("Coffe ready!\n");
	return (NULL);
}

int	main(void)
{

	pthread_t	starbucks_workers[10];

	for (int i = 0; i < 10; i++)
	{
		pthread_create(starbucks_workers + i, NULL, make_coffee, NULL);
	}

	for (int i = 0; i < 10; i++)
	{
		pthread_join(starbucks_workers[i], NULL);
	}

	return (0);
}
*/

//4rth Version (thread id)
/*
void	*make_coffee(void *data)
{
	printf("Worker preparing coffee\n");
	sleep(5);//Modify if you want to check thread info in System Monitor app
	printf("Coffe ready!\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	starbucks_workers[10];

	for (int i = 0; i < 10; i++)
	{
		pthread_create(starbucks_workers + i, NULL, make_coffee, NULL);
	}

	for (int i = 0; i < 10; i++)
	{
		pthread_join(starbucks_workers[i], NULL);
	}

	//Loop to identify thread id:
	for (int i = 0; i < 10; i++)
	{
		printf("Starbucks worker (thread) id: %lu\n", starbucks_workers[i]);
	}

	return (0);
}
*/

//Version with data
//In this version you'll see that the order in which printfs are  printed is different each time
//for both the 'worker preparing coffee' message & 'coffee ready'
//It is because all process are parallel and are set to 'sleep' the same time -takes tha same time-


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*make_coffee(void *data)
{
	int worker_id = *(int *)data;  // Dereference the pointer to obtein 'i' value
	printf("Worker %d preparing coffee\n", worker_id);
	sleep(20);
	printf("Coffee %d ready!\n", worker_id);
	return (NULL);
}

int	main(void)
{
	pthread_t	starbucks_workers[10];
	int worker_ids[10]; // Array to allocate workers IDs

	for (int i = 0; i < 10; i++)
	{
		worker_ids[i] = i;  // Asigna index to worker_ids[i]
		pthread_create(&starbucks_workers[i], NULL, make_coffee, &worker_ids[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		pthread_join(starbucks_workers[i], NULL);
	}

	return (0);
}

