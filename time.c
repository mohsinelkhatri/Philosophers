/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:51:14 by melkhatr          #+#    #+#             */
/*   Updated: 2025/11/10 14:14:36 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	busy_sleep_ms(long ms)
{
	long	start;

	start = now_ms();
	while (now_ms() - start < ms)
		usleep(200);
}

void	chunk_sleep(t_sim *sim, long ms)
{
	long	start;

	start = now_ms();
	while (!get_stopped(sim))
	{
		if (now_ms() - start >= ms)
			break ;
		usleep(200);
	}
}
