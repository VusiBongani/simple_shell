#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point
 * Return: returns void
 */

int main(void)
{
	int totalStudents = 0;

	printf("Enter the number of students in the class: ");
	scanf("%d", &totalStudents);

	printf("The total number of students in the class is: %d\n", totalStudents);

	return (0);
}
