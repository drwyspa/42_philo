/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:20:17 by pjedrycz          #+#    #+#             */
/*   Updated: 2024/10/22 21:24:29 by pjedrycz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
