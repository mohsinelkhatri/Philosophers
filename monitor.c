/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 08:50:51 by melkhatr          #+#    #+#             */
/*   Updated: 2025/10/07 08:53:45 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	everyone_full(t_sim *sim)
{
	int	i;
	int	full;

	full = 1;
	if (sim->must_eat < 0)
		return (0);
	i = 0;
	while (i < sim->n)
	{
		pthread_mutex_lock(&sim->philos[i].meal_mtx);
		if (sim->philos[i].meals_done < sim->must_eat)
			full = 0;
		pthread_mutex_unlock(&sim->philos[i].meal_mtx);
		if (!full)
			break ;
		i++;
	}
	return (full);
}

static int	check_death(t_sim *sim, int i)
{
	long	last;

	pthread_mutex_lock(&sim->philos[i].meal_mtx);
	last = sim->philos[i].last_meal_ms;
	pthread_mutex_unlock(&sim->philos[i].meal_mtx);
	if (now_ms() - last >= sim->t_die)
	{
		set_stopped(sim, 1);
		print_state(sim, sim->philos[i].id, "died", 1);
		return (1);
	}
	return (0);
}

static int	scan_once(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->n && !get_stopped(sim))
	{
		if (check_death(sim, i))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	while (!get_stopped(sim))
	{
		if (scan_once(sim))
			return (NULL);
		if (everyone_full(sim))
		{
			set_stopped(sim, 1);
			return (NULL);
		}
		usleep(200);
	}
	return (NULL);
}
