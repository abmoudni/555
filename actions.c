#include "philo.h"

void print_action(t_philo *philo, char *msg) {
    pthread_mutex_lock(&philo->params->print_lock);
    if (!philo->params->someone_died)
        printf("%ld %d %s\n", get_time_ms() - philo->params->start_time,
               philo->id + 1, msg);
    pthread_mutex_unlock(&philo->params->print_lock);
}

void take_forks(t_philo *philo) {
    int id = philo->id;
    int left = id;
    int right = (id + 1) % philo->params->num_philos;

    if (id % 2 == 0) {
         usleep(200);

        pthread_mutex_lock(&philo->params->forks[left]);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(&philo->params->forks[right]);
        print_action(philo, "has taken a fork");
    } else {
        pthread_mutex_lock(&philo->params->forks[right]);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(&philo->params->forks[left]);
        print_action(philo, "has taken a fork");
    }
}

void release_forks(t_philo *philo) {
    pthread_mutex_unlock(&philo->params->forks[philo->id]);
    pthread_mutex_unlock(&philo->params->forks[(philo->id + 1) % philo->params->num_philos]);
}

void eat(t_philo *philo) {
    print_action(philo, "is eating");
    philo->last_meal_time = get_time_ms();
    philo->meals_eaten++;
    usleep(philo->params->time_to_eat * 1000);
}

void go_to_sleep(t_philo *philo) {
    print_action(philo, "is sleeping");
    usleep(philo->params->time_to_sleep * 1000);
}

void think(t_philo *philo) {
    print_action(philo, "is thinking");
}
