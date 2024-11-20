#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int	index = *(int*)arg;
	int	sum = 0;
	for (int j = 0; j < 5; j++)
		sum += primes[index + j];
	*(int*)arg = sum;
	return (arg);
}

int	main(int argc, char *argv[])
{
	pthread_t	th[2];
	int	i;
	for (i = 0; i < 2; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i * 5;//index 0 for 1rst thr and index 5 for 2nd thr
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread");
		}
	}
	int	globalSum = 0;
	for (i = 0; i < 2; i++)
	{
		int *r;
		if (pthread_join(th[i], &r) != 0)
		{
			perror("Failed to create thread");
		}
		globalSum += *r;
		free(r);
	}
	printf("Global sum+ %d\n", globalSum);
	return (0);
}

/*
int	mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (long i = 0; i < 100000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	th[4];
	int	i;


	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
			return 1;
		}
		printf("Thread %d has started\n", i);
	}
	for (i = 0; i < 4; i++)
	{
		if(pthread_join(th[i], NULL) != 0)
		{
			perror("Failed join thread");
			return 2;
		}
		printf("Thread %d has finished\n", i);

	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}
*/

//Race condition + mutex

//long	mails = 0;

/* trying to solve race conditions with variable + sleep
int	lock = 0;

void	*routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		if (lock == 1)
			sleep(10);//wait for 10 sec
		lock = 1;
		mails++;
		lock = 0;
	}
	return (NULL);
}
*/
/*
pthread_mutex_t	mutex;


void	*routine()
{
	for (long i = 0; i < 100000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	t1, t2;

	pthread_mutex_init(&mutex, NULL);
	if(pthread_create(&t1, NULL, &routine, NULL) != 0)
		return 1;
	if(pthread_create(&t2, NULL, &routine, NULL) != 0)
		return 2;
	if(pthread_join(t1, NULL) != 0)
		return 3;
	if(pthread_join(t2, NULL) != 0)
		return 4;

	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %ld\n", mails);
	return (0);
}
*/
/* intro
void	*routine()
{
	printf("Test from threads\n");
	sleep(3);
	printf("Ending thread\n");
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	t1, t2;

	if(pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);//If a pthread function works returns 0 else != 0 PROTECT
	pthread_create(&t1, NULL, &routine, NULL);

	pthread_join(t1, NULL);
	pthread_join(t1, NULL);

	return (0);
}
*/

/*
void	*computation(void *add)
{
	long	sum = 0;
	long	*add_num = (long *) (add);

	for (long i = 0; i < 1000000000; i++)
	{
		sum += *add_num;
	}
	//printf("Add: %ld\n", *add_num);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;

	
	long value1 = 1;
	long value2 = 2;

//	computation((void *) &value1);
//	computation((void *) &value2);


	pthread_create(&thread1, NULL, computation, (void*)&value1);
//	pthread_join(thread1, NULL);//This makes wait for that threat
	pthread_create(&thread2, NULL, computation, (void*)&value2);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	return (0);
}
*/
