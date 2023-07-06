#include "Pch.h"
#include "Colour.h"

Color Colour(int r, int g, int b, int a)
{
	Color col;
	col.A = a;
	col.R = r;
	col.G = g;
	col.B = b;
	return col;
}