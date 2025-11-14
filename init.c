#include "philo.h"

int init_mutexes(t_params *params) {
    int i = 0;
    params->forks = malloc(sizeof(pthread_mutex_t) * params->num_philos);
    if (!params->forks) return (1);
    while (i < params->num_philos) {
        if (pthread_mutex_init(&params->forks[i], NULL) != 0)
            return (1);
        i++;
    }
    if (pthread_mutex_init(&params->print_lock, NULL) != 0)
        return (1);
    return (0);
}

int init_philos(t_params *params, t_philo **philos) {
    int i = 0;
    *philos = malloc(sizeof(t_philo) * params->num_philos);
    if (!*philos) return (1);
    while (i < params->num_philos) {
        (*philos)[i].id = i;
        (*philos)[i].meals_eaten = 0;
        (*philos)[i].last_meal_time = get_time_ms();
        (*philos)[i].params = params;
        i++;
    }
    return (0);
}

int start_threads(t_params *params, t_philo *philos) {
    int i = 0;
    params->start_time = get_time_ms();
    while (i < params->num_philos) {
        if (pthread_create(&philos[i].thread, NULL, philosopher_thread, &philos[i]) != 0)
            return (1);
        usleep(100);
        i++;
    }
    return (0);
}
