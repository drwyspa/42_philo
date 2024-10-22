/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:06:43 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/10/22 21:46:12 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Gets the current time in miliseconds - global time since Epoch (1970-01-01 00:00:00).
	Returns the time value, converted in miliseconds.
*/
time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
	Pauses the philosopher thread for a certain amount of time in miliseconds.
	Periodically checks to see if the simulation has ended during the sleep
	time and cuts the sleep short if it has.
*/
void	philo_sleep(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (has_sim_stopped(table))
			break;
		usleep(100);
	}
}

/*
	Waits for all the threads execution.
	This allows all threads starts with the same start time reference.
	Synchronizes philo_control thread with philosophers threads.
*/
void	sim_start_delay(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue;
}
