#include "philo.h"

int parse_args(int argc, char **argv, t_params *params) {
    if (argc != 5 && argc != 6)
        return (1);

    params->num_philos = ft_atoi(argv[1]);
    params->time_to_die = ft_atoi(argv[2]);
    params->time_to_eat = ft_atoi(argv[3]);
    params->time_to_sleep = ft_atoi(argv[4]);

    if (argc == 6)
        params->must_eat_count = ft_atoi(argv[5]);
    else
        params->must_eat_count = -1;

    params->someone_died = 0;

    return (0);
}


int main(int argc, char **argv) {
    t_params params;
    t_philo *philos;
    pthread_t monitor;
    int i = 0;

    if (parse_args(argc, argv, &params)) {
        printf("Usage: ./philo num_philos time_to_die time_to_eat time_to_sleep [must_eat]");
        return (1);
    }

    if (init_mutexes(&params) || init_philos(&params, &philos))
        return (1);
    if (start_threads(&params, philos))
        return (1);

    pthread_create(&monitor, NULL, monitor_routine, philos);
    pthread_join(monitor, NULL);

    while (i < params.num_philos) {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
    return (0);
}
