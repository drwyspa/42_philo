/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:17:29 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/10/22 22:45:40 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

// Macros //

# define MAX_PHILOS 250
# define STR_MAX_PHILOS "250"

# ifndef DEBUG_FORMATTING
#  define DEBUG_FORMATTING 0
# endif

# define NC		"\ec[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define STR_PROG_NAME			"philo:"
# define STR_USAGE				"%s usage: ./philo <number_of_philos> \
								<time_to_die> <tine_to_eat> <time_to_sleep> \
								[number_of_meals]\n"
# define STR_ERR_INPUT_DIGIT	"%s invalid input: %s: \
								use only INTs from 0 to INT_MAX.\n"
# define STR_ERR_INPUT_POFLOW	"%s invalid input: \
								you need between 1 and %s philos.\n"
# define STR_ERR_THREAD			"%s error: Thread creation failed.\n"
# define STR_ERR_MALLOC			"%s error: Memory allocation failed.\n"
# define STR_ERR_MUTEX			"%s error: Mutex creation failed.\n"

// Structures //

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	times_eat;
	unsigned int	fork[2];
	pthread_mutex_t	meal_time_lock;
	time_t			last_meal;
	t_table			*table;
} t_philo;

typedef struct s_table
{
	time_t			start_time;
	unsigned int	nb_philos;
	pthread_t		philo_control;// Main thread - checks if anyone died or all philos ate all the meals.
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meals_cnt;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philos;
} t_table;

//Do I need values here?
//By default, first one is 0.
typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
} t_status;

// Function prototypes //


// Parsing
int		atoi_int(char *str);
bool	is_valid_input(int argc, char **argv);

// Init
t_table	*init_table(int argc, char **argv, int i);

// Routines


// Time
time_t	get_time_in_ms(void);
void	philo_sleep(t_table *table, time_t sleep_time);
void	sim_start_delay(time_t start_time);

// Output
int		msg(char *str, char *detail, int exit_no);
void	*error_null(char *str, char *details, t_table *table);
void	write_status(t_philo *philo, bool control_report, t_status status);
void	write_outcome(t_table *table);

// Philo control
bool	has_sim_stopped(t_table *table);

// Exit
void	*free_table(t_table *table);
int		error_failure(char *str, char *details, t_table *table);
void	destroy_mutexes(t_table *table);

#endif