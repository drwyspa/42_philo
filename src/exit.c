/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 22:03:43 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/10/25 21:30:38 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Frees all the allocated memory.
	Return a NULL pointer if nothing was allocated or already freed.
*/
void	*free_table(t_table *table)
{
	unsigned int	i;

	i = 0;
	if (!table)
		return (NULL);
	if (table->fork_locks != NULL)
		free(table->fork_locks);
	if (table->philos != NULL)
	{
		while (i < table->nb_philos)
		{
			if (table->philos[i] != NULL)
				free(table->philos[i]);
			i++;
		}
		free(table->philos);
	}
	free(table);
	return (NULL);
}

/*
	Destroy all mutexes: forks, meal locks, write and sim stopper lock.
*/
void	destroy_mutexes(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->fork_locks[i]);
		pthread_mutex_destroy(&table->philos[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->sim_stop_lock);
}

/* 
	Error management. Writes error message in terminal.
	Returns exit number.
*/
int	msg(char *str, char *detail, int exit_no)
{
	if (!detail)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (exit_no);
}

/*
	Error management for initialization.
	Frees all allocated memory, return error message and 0 as a fail.
*/
int	error_failure(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	return (msg(str, details, 0));
}

/*
	Error management for initialization.
	Frees allocated memory. Returns error message and a NULL pointer.
*/
void	*error_null(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	msg(str, details, EXIT_FAILURE);
	return (NULL);
}
