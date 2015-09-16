#include "stdafx.h"

int AppleStockCalculator(int stockArray[], int size)
{
	int maxReturn = 0;

	for (int i = 0; i < size; ++i)
	{
		int base = stockArray[i];
		for (int j = i + 1; j < size; ++j)
		{
			if (stockArray[j] - base > maxReturn)
			{
				maxReturn = stockArray[j] - base;
			}
		}
	}

	return maxReturn;
}