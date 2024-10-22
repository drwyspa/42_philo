/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:37:50 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/10/22 21:52:08 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	For only one philosopher.
	A single philosopher only has one fork, and so cannot eat. The
	philosopher will pick up that fork, wait as long as time_to_die and die.
	This is a separate routine to make sure that the thread does not get
	stuck waiting for the second fork in the eat routine.
*/
static void	*one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);////////////
}

/*
	The philosopher thread routine. The philosopher must eat, sleep
	and think. In order to avoid conflicts between philosopher threads,
	philosophers with an even id start by thinking, which delays their
	meal time by a small margin. This allows odd-id philosophers to
	grab their forks first, avoiding deadlocks.
*/
void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->meals_cnt == 0)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_time_lock);
	sim_start_delay(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->nb_philos == 1)
		return (one_philo_routine(philo));////////////
}