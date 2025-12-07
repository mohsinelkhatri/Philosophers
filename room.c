/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 08:51:06 by melkhatr          #+#    #+#             */
/*   Updated: 2025/10/07 08:53:07 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	room_enter(t_sim *sim)
{
	while (!get_stopped(sim))
	{
		pthread_mutex_lock(&sim->room_mtx);
		if (sim->room_tokens > 0)
		{
			sim->room_tokens--;
			pthread_mutex_unlock(&sim->room_mtx);
			return ;
		}
		pthread_mutex_unlock(&sim->room_mtx);
		usleep(200);
	}
}

void	room_leave(t_sim *sim)
{
	pthread_mutex_lock(&sim->room_mtx);
	sim->room_tokens++;
	pthread_mutex_unlock(&sim->room_mtx);
}
