/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:17:49 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/10/22 21:37:15 by pjedrycz         ###   ########.fr       */
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
			&philosopher, /////////////////////))
	}
}

int main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc -1 < 4 || argc - 1 > 5)
		return (msg(STR_USAGE, NULL, EXIT_FAILURE));
	if (!is_vlid_input(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv, 1);
	if (!table)
		return (EXIT_FAILURE);
	//////////if (!start_simulation(table))
}