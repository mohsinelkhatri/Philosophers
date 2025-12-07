/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:50:21 by melkhatr          #+#    #+#             */
/*   Updated: 2025/10/07 08:54:53 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(t_philo *p)
{
	t_sim	*sim;

	sim = p->sim;
	pthread_mutex_lock(&p->meal_mtx);
	p->last_meal_ms = now_ms();
	pthread_mutex_unlock(&p->meal_mtx);
	print_state(sim, p->id, "is eating", 0);
	chunk_sleep(sim, sim->t_eat);
	pthread_mutex_lock(&p->meal_mtx);
	p->meals_done += 1;
	pthread_mutex_unlock(&p->meal_mtx);
}

void	do_sleep_think(t_philo *p)
{
	print_state(p->sim, p->id, "is sleeping", 0);
	chunk_sleep(p->sim, p->sim->t_sleep);
	print_state(p->sim, p->id, "is thinking", 0);
	if (p->sim->n % 2 == 1)
		usleep(1000);
}
