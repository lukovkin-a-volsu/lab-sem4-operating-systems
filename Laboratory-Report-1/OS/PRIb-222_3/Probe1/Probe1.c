#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void main()
{
	double a = 0.0, b = 0.0, c = 0.0, s = 0.0;
	_cprintf("sqrt(a + b) / c \n");
	_cprintf("Input a, b, c: \n");
	scanf("%lf %lf %lf", &a, &b, &c);
	s = sqrt(a + b) / c;
	_cprintf("Result: \n");
	printf("%.3f\n", s);		
	_cprintf("%.3f\n", s);
}