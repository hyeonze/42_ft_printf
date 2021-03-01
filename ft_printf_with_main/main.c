#include "ft_printf.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	printf("COM > \n");
	int num = 10;
	void *ptr = &num;
	int comret = printf("%8.0p", 0);

	printf("\n");

	printf("MY  > \n");
	int myret = ft_printf("%8.0p", 0);

	printf("\n");

	printf("COMRET > %d", comret);

	printf("\n");
	
	printf("MYRET  > %d", myret);

	return (0);

	//printf("rules of %%d\n");
	//printf("%7.9d\n", 12345);
	//printf("%9.7d\n", 12345);
	//printf("%5.7d\n", 12345);
	//printf("%7.3d\n", 12345);
	//printf("%1.3d\n", 12345);
	//printf("%3.1d\n", 12345);
	//printf("\nrules of %%s\n");
	//printf("%7.9s\n", "abcde");
	//printf("%9.7s\n", "abcde");
	//printf("%5.7s\n", "abcde");
	//printf("%7.3s\n", "abcde");
	//printf("%1.3s\n", "abcde");
	//printf("%3.1s\n", "abcde");
}
