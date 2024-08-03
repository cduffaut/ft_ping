#include "../h/ft_ping.h"

long double ft_pow(long double nbr)
{
	return (nbr * nbr);
}

// long int		ft_sqrt(long int nbr)
// {
// 	if (nbr <= 0)
// 		return (0);
	
// 	long int i = 0;
// 	while (i * i <= nbr && i <= 1073741824)
// 	{
// 		if (i * i == nbr)
// 			return (i);
// 		i++;
// 	}
// 	return (i - 1);
// }

double ft_sqrt(float nbr)
{
    // for 0 and 1, the square roots are themselves
    if (nbr < 2)
        return nbr;
 
    // considering the equation values
    double relais = nbr;
    double final = (relais + (nbr / relais)) / 2;
 
    // as we want to get upto 3 decimal digits, the absolute
    // difference should not exceed 0.001
    while ((relais - final) >= 0.001)
    {
        relais = final;
        final = (relais + (nbr / relais)) / 2;
    }
    return final;
}

float ft_avg(int len)
{
	t_linked_list *relais;
	float	sum = 0;

	relais = list.li;
	while (relais)
	{
		sum += relais->nbr;
		relais = relais->next;
	}
	
	float avg = sum / len;
    return (avg);
}

float ft_stddev(int len)
{
	t_linked_list *relais;
    float avg = ft_avg(len);
	float tmp = 0;

	relais = list.li;
	while (relais)
	{	
		tmp += ft_pow(relais->nbr - avg);
		relais = relais->next;
	}

	float variance = tmp / (len - 1);

	double stddev = ft_sqrt(variance);

	return ((float)stddev);
}

float ft_min()
{
	t_linked_list *relais;

	relais = list.li;
    float min = relais->nbr;
    while (relais)
    {
        if (relais->nbr < min)
            min = relais->nbr;
		relais = relais->next;
    }
    return (min);
}

float ft_max()
{
	t_linked_list *relais;

	relais = list.li;
    float max = relais->nbr;

    while (relais)
    {
        if (relais->nbr > max)
            max = relais->nbr;
		relais = relais->next;
    }
    return (max);
}
