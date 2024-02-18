#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void main()
{
	double s = 0.0;
	scanf_s("%lf", &s);
	s = pow(s, 1.0 / 6);
	printf("%f\n", s);
	_cprintf("%f\n", s);
}