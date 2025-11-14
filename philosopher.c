#include "philo.h"

void *philosopher_thread(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_params *params = philo->params;

    if (params->num_philos == 1)
    {
        take_forks(philo);
        usleep(params->time_to_die * 1000);
        return (NULL);
    }

    while (!params->someone_died)
    {
        take_forks(philo);
        eat(philo);
        release_forks(philo);
        go_to_sleep(philo);
        think(philo);
    }
    return (NULL);
}
