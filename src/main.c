#include "../includes/philo.h"

long start_time;

long get_current_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void print_status(int id, const char *status) {
    long timestamp = get_current_time();
    printf("%ld %d %s\n", timestamp, id, status);
}

void init_specs(t_specs *specs, int n_philos) {
    specs->n_philos = n_philos;
    specs->forks = malloc(sizeof(pthread_mutex_t) * n_philos);
    for (int i = 0; i < n_philos; i++) {
        pthread_mutex_init(&specs->forks[i], NULL);
    }
    pthread_mutex_init(&specs->lock, NULL);
    specs->stop = 0;
}

void init_philosophers(t_philo *philos, t_specs *specs, int n_philos) {
    for (int i = 0; i < n_philos; i++) {
        philos[i].id = i;
        philos[i].left_fork = i;
        philos[i].right_fork = (i + 1) % n_philos;
        philos[i].n_eaten = 0;
        philos[i].last_meal = get_current_time();
        philos[i].specs = specs;
    }
}

void better_usleep(int microseconds) {
    struct timeval start, current;
    gettimeofday(&start, NULL);
    long elapsed;

    do {
        // usleep(100); // Schlafen für 50 Mikrosekunden
        gettimeofday(&current, NULL);
        elapsed = (current.tv_sec - start.tv_sec) * 1000 + (current.tv_usec - start.tv_usec) / 1000;
    } while (elapsed < microseconds);
}

void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    t_specs *specs = philo->specs;

    while (!specs->stop) {
        long current_time = get_current_time();
        if (current_time - philo->last_meal > specs->time_to_die) {
            print_status(philo->id, "died");
            specs->stop = 1;
            break;
        }

        // Denken
        print_status(philo->id, "is thinking");

        // Gabeln nehmen
        pthread_mutex_lock(&specs->lock);
        pthread_mutex_lock(&specs->forks[philo->left_fork]);
        print_status(philo->id, "has taken a fork");
        pthread_mutex_lock(&specs->forks[philo->right_fork]);
        print_status(philo->id, "has taken a fork");
        pthread_mutex_unlock(&specs->lock);

        // Essen
        print_status(philo->id, "is eating");
        philo->last_meal = get_current_time();
        philo->n_eaten++;
        better_usleep(specs->time_to_eat);

        // Gabeln zurücklegen
        pthread_mutex_unlock(&specs->forks[philo->right_fork]);
        pthread_mutex_unlock(&specs->forks[philo->left_fork]);

        // Schlafen
        print_status(philo->id, "is sleeping");
        better_usleep(specs->time_to_sleep);

        // Häufigere Überprüfung des Todeszustands
        // better_usleep(100); // 1 ms Pause zwischen den Überprüfungen
    }

    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s n_philos time_to_die time_to_eat time_to_sleep\n", argv[0]);
        return 1;
    }

    int n_philos = atoi(argv[1]);
    int time_to_die = atoi(argv[2]);
    int time_to_eat = atoi(argv[3]);
    int time_to_sleep = atoi(argv[4]);

    t_specs specs;
    init_specs(&specs, n_philos);
    specs.time_to_die = time_to_die;
    specs.time_to_eat = time_to_eat;
    specs.time_to_sleep = time_to_sleep;

    t_philo philos[n_philos];
    init_philosophers(philos, &specs, n_philos);

    pthread_t threads[n_philos];
    for (int i = 0; i < n_philos; i++) {
        pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]);
    }

    for (int i = 0; i < n_philos; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < n_philos; i++) {
        pthread_mutex_destroy(&specs.forks[i]);
    }
    pthread_mutex_destroy(&specs.lock);
    free(specs.forks);

    return 0;
}