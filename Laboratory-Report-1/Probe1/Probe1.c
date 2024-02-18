#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void main()
{
	double a = 0.0, b = 0.0, c = 0.0, s = 0.0;
	scanf_s("%lf %lf %lf", &a, &b, &c);
	s = sqrt(a + b) / c;
	printf("%f\n", s);		
	_cprintf("%f\n", s);
}