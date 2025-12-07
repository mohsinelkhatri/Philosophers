/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:50:26 by melkhatr          #+#    #+#             */
/*   Updated: 2025/10/09 14:51:01 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_and_join(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->n)
		pthread_join(sim->philos[i++].thread, NULL);
	pthread_join(sim->monitor, NULL);
}

void	destroy_sim(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->n)
		pthread_mutex_destroy(&sim->forks[i++]);
	i = 0;
	while (i < sim->n)
		pthread_mutex_destroy(&sim->philos[i++].meal_mtx);
	pthread_mutex_destroy(&sim->print_mtx);
	pthread_mutex_destroy(&sim->stop_mtx);
	pthread_mutex_destroy(&sim->room_mtx);
	free(sim->forks);
	free(sim->philos);
}
