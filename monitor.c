#include "philo.h"

int check_death(t_philo *philo) {
    if (get_time_ms() - philo->last_meal_time >= philo->params->time_to_die) {
        pthread_mutex_lock(&philo->params->print_lock);
        if (!philo->params->someone_died) {
            printf("%ld %d died\n", get_time_ms() - philo->params->start_time, philo->id + 1);
            philo->params->someone_died = 1;
        }
        pthread_mutex_unlock(&philo->params->print_lock);
        return (1);
    }
    return (0);
}

int all_ate_enough(t_philo *philos, t_params *params) {
    int i = 0;
    if (params->must_eat_count == -1)
        return (0);
    while (i < params->num_philos) {
        if (philos[i].meals_eaten < params->must_eat_count)
            return (0);
        i++;
    }
    return (1);
}

void *monitor_routine(void *arg) {
    t_philo *philos = (t_philo *)arg;
    t_params *params = philos[0].params;

    while (!params->someone_died) {
        int i = 0;
        while (i < params->num_philos) {
            if (check_death(&philos[i]))
                return NULL;
            i++;
        }
        if (all_ate_enough(philos, params))
            return NULL;
        usleep(1000);
    }
    return NULL;
}
