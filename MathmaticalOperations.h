#ifndef MATHOP
#define MATHOP

float subtractPercentageFromNumber(float number, float percent)
{
	return (100 - percent) / 100;
}

float clamp(float max, float min, float number)
{
	if(number < min)
	{
		return min;
	}
	if(number > max)
	{
		return max;
	}
	return number;
}

#endif