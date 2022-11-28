#include "philosopher.h"

int	ft_atoi(const char *nptr)
{
	long long   res;
	int	sign;

	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	res = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - 48;
		nptr++;
	}
	return (sign * res);
}