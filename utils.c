#include "philo.h"

long get_time_ms(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}


//void smart_sleep(long duration_ms, t_params *params)
//{
 //   long start = get_time_ms();
   // while (get_time_ms() - start < duration_ms)
   // {
   //     usleep(500); 
   // }
//}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sing;
	int	res;

	i = 0;
	sing = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sing = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	res = 0;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sing);
}