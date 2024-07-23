#include "../includes/philo.h"
#include "../includes/stylesheet.h"


/*
 * Copilot Norm Enforcement Guidelines
 *
 * Naming Conventions:
 * - Structure names must start with 's_'.
 * - Typedef names must start with 't_'.
 * - Union names must start with 'u_'.
 * - Enum names must start with 'e_'.
 * - Global variable names must start with 'g_'.
 * - Variables, functions, files, and directories must use only lowercase letters, digits, and underscores.
 * - Use snake_case for all identifiers.
 * - All identifiers must be in English.
 * - Choose the most explicit or mnemonic names possible.
 * - Global variables that are not marked const and static are forbidden unless explicitly allowed.
 *
 * Formatting Rules:
 * - Indent code with 4-space tabs.
 * - Functions must be a maximum of 25 lines, excluding the function's own curly brackets.
 * - Each line must be at most 80 columns wide.
 * - Separate functions with a newline.
 * - Only one instruction per line.
 * - No trailing spaces or tabs on any line.
 * - No consecutive spaces.
 * - Start a new line after each curly bracket or end of a control structure.
 * - Each comma or semicolon must be followed by a space, unless it's the end of a line.
 * - Operators and operands must be separated by exactly one space.
 * - C keywords must be followed by a space, except for type keywords (e.g., int, char, float).
 * - Variable declarations must be indented on the same column within their scope.
 * - Pointers must have their asterisks adjacent to variable names.
 * - Only one variable declaration per line.
 * - Declaration and initialization cannot be on the same line, except for global variables, static variables, and constants.
 * - Declarations must be at the beginning of a function.
 * - Place an empty line between variable declarations and the rest of the function's code. No other empty lines are allowed within a function.
 * - Multiple assignments on a single line are forbidden.
 * - Control structures (if, while, etc.) must have braces, unless they contain a single line.
 *
 * Function Rules:
 * - A function can take a maximum of 4 named parameters.
 * - Functions with no arguments must be explicitly prototyped with the word "void".
 * - Parameter names in function prototypes must be named.
 * - No more than 5 variables can be declared per function.
 * - Function returns must be enclosed in parentheses.
 *
 * Typedef, Struct, Enum, and Union:
 * - Follow specific indentation rules when declaring these types.
 * - Do not declare structures in a .c file.
 *
 * Header Files:
 * - Only include declarations, defines, prototypes, and macros.
 * - All includes must be at the beginning of the file.
 * - Protect header files from double inclusion.
 *
 * Forbidden:
 * - You’re not allowed to use for, do...while, switch, case, or goto.
 * - Ternary operators and Variable Length Arrays (VLAs) are forbidden.
 *
 * Comments:
 * - Comments must be in English and useful.
 * - Comments cannot be inside functions’ bodies, except at the end of a line or on their own line.
 */




void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    t_specs *specs = philo->specs;

    while (1) {

		pthread_mutex_lock(&specs->stop_mutex);
		int stop = specs->stop;
		pthread_mutex_unlock(&specs->stop_mutex);
		if (stop == 1) {
			break;
		}

        // Denken
        print_status(philo->id, "is thinking", specs);

        // Gabeln nehmen
        if (philo->id % 2 == 0) {
            pthread_mutex_lock(&specs->lock);
            pthread_mutex_lock(&specs->forks[philo->left_fork]);
            print_status(philo->id, "has taken a fork", specs);
            pthread_mutex_lock(&specs->forks[philo->right_fork]);
            print_status(philo->id, "has taken a fork", specs);
            pthread_mutex_unlock(&specs->lock);
        } else {
            pthread_mutex_lock(&specs->forks[philo->right_fork]);
            print_status(philo->id, "has taken right fork");
            pthread_mutex_lock(&specs->forks[philo->left_fork]);
            print_status(philo->id, "has taken left fork");
        }

        // Essen
        print_status(philo->id, "is eating", specs);
        philo->last_meal = get_current_time();
        philo->n_eaten++;
        better_usleep(specs->time_to_eat);

        // Gabeln zurücklegen
        pthread_mutex_unlock(&specs->forks[philo->right_fork]);
        pthread_mutex_unlock(&specs->forks[philo->left_fork]);

        // Schlafen
        print_status(philo->id, "is sleeping", specs);
        better_usleep(specs->time_to_sleep);

        // Häufigere Überprüfung des Todeszustands
        // better_usleep(100); // 1 ms Pause zwischen den Überprüfungen
    }

    return NULL;
}

int main(int argc, char **argv) {
    if (check_input(argc, argv) == 1) {
		start_screen();
		wrong_input();
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
	pthread_mutex_init(&specs.stop_mutex, NULL);

    t_philo philos[n_philos];
    init_philosophers(philos, &specs, n_philos);

    pthread_t threads[n_philos];
    int i = 0;
	while (i < n_philos) {
		pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]);
		i++;
	}

	pthread_t monitor_thread;
	if (pthread_create(&monitor_thread, NULL, monitoring, philos) != 0) {
		perror("Failed to create watcher thread");
		// Fehlerbehandlung
	}

	i = 0;
	while (i < n_philos) {
		pthread_join(threads[i], NULL);
		i++;
	}

	// Warten auf das Ende des Überwachungsthreads
	if (pthread_join(monitor_thread, NULL) != 0) {
		perror("Failed to join watcher thread");
		// Fehlerbehandlung
	}

	i = 0;
	while (i < n_philos) {
		pthread_mutex_destroy(&specs.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&specs.lock);
	pthread_mutex_destroy(&specs.stop_mutex);
	free(specs.forks);

    return 0;
}