/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:38:15 by melkhatr          #+#    #+#             */
/*   Updated: 2025/10/29 11:25:28 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	alloc_arrays(t_sim *sim)
{
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->n);
	sim->philos = malloc(sizeof(t_philo) * sim->n);
	if (!sim->forks || !sim->philos)
	{
		if (sim->forks)
			free(sim->forks);
		if (sim->philos)
			free(sim->philos);
		return (ft_putstr_fd("Error\n", 2), -1);
	}
	return (0);
}

static void	init_global_mutexes(t_sim *sim)
{
	pthread_mutex_init(&sim->print_mtx, NULL);
	pthread_mutex_init(&sim->stop_mtx, NULL);
	pthread_mutex_init(&sim->room_mtx, NULL);
	sim->stopped = 0;
}

static void	set_room_tokens(t_sim *sim)
{
	if (sim->n == 1)
		sim->room_tokens = 1;
	else
		sim->room_tokens = sim->n - 1;
}

static void	init_philos(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->n)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].left = i;
		sim->philos[i].right = (i + 1) % sim->n;
		sim->philos[i].last_meal_ms = 0;
		sim->philos[i].meals_done = 0;
		sim->philos[i].sim = sim;
		pthread_mutex_init(&sim->philos[i].meal_mtx, NULL);
		i++;
	}
}

int	sim_init(t_sim *sim)
{
	if (alloc_arrays(sim) != 0)
		return (-1);
	init_forks(sim);
	init_global_mutexes(sim);
	set_room_tokens(sim);
	init_philos(sim);
	return (0);
}
