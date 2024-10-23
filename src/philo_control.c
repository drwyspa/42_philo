/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:20:17 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/10/23 19:03:01 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Sets the simulation stop flag to true or false. Only the philo_control
	thread can set this flag. If the simulation stop flag is
	set to true, that means the simulation has met an end condition.
*/
static void	set_sim_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->sim_stop_lock);
	table->sim_stop = state;
	pthread_mutex_unlock(&table->sim_stop_lock);
}

/*
	Checks whether the simulation is at an end. The stop flag
	is protected by a mutex lock to allow any thread to check
	the simulation status without conflict.
	Returns true if the simulation stop flag is set to true,
	false if the flag is set to false. 
*/
bool	has_sim_stopped(t_table *table)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop == true)
		ret = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (ret);
}

/*
	Checks if the philosopher must be killed by comparing the
	time since the philosopher's last meal and the time_to_die parameter.
	If it is time for the philosopher to die, sets the simulation stop
	flag and displays the death status.
	Returns true if the philosopher has been killed, false if not.
*/
static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		set_sim_stop_flag(philo->table, true);
		write_status(philo, true, DIED);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

/*
	Checks each philosopher to see if one of two end conditions
	has been reached. Stops the simulation if a philosopher needs
	to be killed, or if every philosopher has eaten enough.
	Returns true if an end condition has been reached, false if not.
*/
static bool	end_condition_reached(t_table *table)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_time_lock);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->meals_cnt != -1)
			if (table->philos[i]->times_eat
			< (unsigned int)table->meals_cnt)
			all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_time_lock);
		i++;
	}
	if (table->meals_cnt != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(table, true);
		return (true);
	}
	return (false);
}

/*
	Thread to rule them all - philosopher. Checks if a philosopher must
	be killed and if all philosophers ate enough. If one of those two
	end conditions are reached, it stops the simulation.
*/
void	*philo_control(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->meals_cnt == 0)
		return (NULL);
	set_sim_stop_flag(table, false);
	sim_start_delay(table->start_time);
	while (true)
	{
		if (end_condition_reachec(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
