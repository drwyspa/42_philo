/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:04:21 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/10/25 21:26:02 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Starts simulation by creating philo_control thread
	and threads for each philosophers.
	True for success and false for fail.
*/
static bool	start_sim(t_table *table)
{
	unsigned int	i;

	table->start_time = get_time_in_ms() + (table->nb_philos * 2 * 10);
	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				&philosopher, table->philos[i]) != 0)
			return (error_failure(STR_ERR_THREAD, NULL, table));
		i++;
	}
	if (table->nb_philos > 1)
	{
		if (pthread_create(&table->philo_control, NULL,
				&philo_control, table) != 0)
			return (error_failure(STR_ERR_THREAD, NULL, table));
	}
	return (true);
}

/*
	Waits for all threads to be joined then destroys mutexes and frees
	allocated memory.
*/
static void	stop_sim(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	if (table->nb_philos > 1)
		pthread_join(table->philo_control, NULL);
	if (DEBUG_FORMATTING == true && table->meals_cnt != -1)
		write_outcome(table);
	destroy_mutexes(table);
	free_table(table);
}

/*
	Main function to init all the elements, start the simulation
	and stop it in right moment.
*/
int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc -1 < 4 || argc - 1 > 5)
		return (msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!is_valid_input(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv, 1);
	if (!table)
		return (EXIT_FAILURE);
	if (!start_sim(table))
		return (EXIT_FAILURE);
	stop_sim(table);
	return (EXIT_SUCCESS);
}
