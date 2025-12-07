/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 08:51:00 by melkhatr          #+#    #+#             */
/*   Updated: 2025/11/14 20:54:44 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_stopped(t_sim *sim)
{
	int	v;

	pthread_mutex_lock(&sim->stop_mtx);
	v = sim->stopped;
	pthread_mutex_unlock(&sim->stop_mtx);
	return (v);
}

void	set_stopped(t_sim *sim, int val)
{
	pthread_mutex_lock(&sim->stop_mtx);
	sim->stopped = val;
	pthread_mutex_unlock(&sim->stop_mtx);
}

void	print_state(t_sim *sim, int id, const char *msg, int force)
{
	long	ts;

	pthread_mutex_lock(&sim->print_mtx);
	if (!force && get_stopped(sim))
	{
		pthread_mutex_unlock(&sim->print_mtx);
		return ;
	}
	ts = now_ms() - sim->start_ms;
	printf("%ld %d %s\n", ts, id, msg);
	pthread_mutex_unlock(&sim->print_mtx);
}
