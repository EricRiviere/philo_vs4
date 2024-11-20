#include <stdio.h>
#include <unistd.h>

void	make_coffe(char *name)
{
	printf("Sturbucks worker %s is making coffe...\n", name);
	sleep(3);
	printf("coffe made by %s ready\n", name);
}

int	main()
{
	make_coffe("Luca");
	make_coffe("Paolo");
	return (0);
}

