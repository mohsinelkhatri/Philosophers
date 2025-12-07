/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:58:39 by melkhatr          #+#    #+#             */
/*   Updated: 2025/10/29 11:26:31 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_last_meal_times(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->n)
	{
		pthread_mutex_lock(&sim->philos[i].meal_mtx);
		sim->philos[i].last_meal_ms = sim->start_ms;
		pthread_mutex_unlock(&sim->philos[i].meal_mtx);
		i++;
	}
}

int	start_threads(t_sim *sim)
{
	int	i;

	sim->start_ms = now_ms();
	init_last_meal_times(sim);
	i = 0;
	while (i < sim->n)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, philo_routine,
				&sim->philos[i]) != 0)
			return (ft_putstr_fd("Error", 2), -1);
		i++;
	}
	if (pthread_create(&sim->monitor, NULL, monitor_routine, sim) != 0)
		return (ft_putstr_fd("Error\n", 2), -1);
	return (0);
}
