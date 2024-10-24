/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:53:06 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/10/24 21:35:55 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Prints the philosopher's status in an easier to read,
	colorful format to help with debugging. For fork-taking
	statuses, extra information is displayed to show which fork
	the philosopher has taken.
*/
static void	print_status_debug(t_philo *philo, char *color,
								char *str, t_status status)
{
	if (status == GOT_FORK_1)
		printf("[%10ld]\t%s%03d\t%s\e[0m: fork [%d]\n",
			get_time_in_ms() - philo->table->start_time,
			color, philo->id + 1, str, philo->fork[0]);
	else if (status == GOT_FORK_2)
		printf("[%10ld]\t%s%03d\t%s\e[0m: fork [%d]\n",
			get_time_in_ms() - philo->table->start_time,
			color, philo->id + 1, str, philo->fork[1]);
	else
		printf("[%10ld]\t%s%03d\t%s\e[0m\n",
			get_time_in_ms() - philo->table->start_time,
			color, philo->id + 1, str);
}

/*
	If debug mode is on (DEBUG_FORMATTING == 1 in philo.h)
	redirects status writing for this mode.
*/
static void	write_status_debug(t_philo *philo, t_status status)
{
	if (status == DIED)
		print_status_debug(philo, RED, "died", status);
	else if (status == EATING)
		print_status_debug(philo, GREEN, "is eating", status);
	else if (status == SLEEPING)
		print_status_debug(philo, CYAN, "is sleeping", status);
	else if (status == THINKING)
		print_status_debug(philo, CYAN, "is thinking", status);
	else if (status == GOT_FORK_1)
		print_status_debug(philo, PURPLE, "has taken a fork", status);
	else if (status == GOT_FORK_2)
		print_status_debug(philo, PURPLE, "has taken a fork", status);
}

/*
	Prints philosopher status in format:
		timestamp_in_ms X status
*/
static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->id + 1, str);
}

/*
	Prints the status of a philosopher as long as the simulation is
	still active. Locks the write mutex to avoid intertwined messages
	from different threads.

	If DEBUG_FORMATTING is set to 1 in philo.h, the status will
	be formatted with colors and extra information to help with debugging.
	Otherwise the output will be the regular format required by the project
	subject.
*/
void	write_status(t_philo *philo, bool control_report, t_status status)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (has_sim_stopped(philo->table) == true
			&& control_report == false)
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return;
	}
	if (DEBUG_FORMATTING == true)
	{
		write_status_debug(philo, status);
		pthread_mutex_unlock(&philo->table->write_lock);
		return;
	}
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->write_lock);	
}

void	write_outcome(t_table *table)
{
	unsigned int	i;
	unsigned int	full_cnt;
	
	full_cnt = 0;
	i = 0;
	while (i < table->nb_philos)
	{
		if (table->philos[i]->times_eat >= (unsigned int)table->meals_cnt)
			full_cnt++;
		i++;
	}
	pthread_mutex_lock(&table->write_lock);
	printf("%d/%d philosophers had at least %d meals.\n",
		full_cnt, table->nb_philos, table->meals_cnt);
	pthread_mutex_unlock(&table->write_lock);
	return;
}
