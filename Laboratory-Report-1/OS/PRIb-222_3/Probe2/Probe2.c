#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void main()
{
	double s = 0.0;
	_cprintf("s = pow(s, 1.0 / 6) \n");
	_cprintf("Input s: \n");
	scanf("%lf", &s);
	s = pow(s, 1.0 / 6);
	_cprintf("Result: ");
	printf("%.3f\n", s);
	_cprintf("%.3f\n", s);
}