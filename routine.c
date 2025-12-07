/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 08:51:10 by melkhatr          #+#    #+#             */
/*   Updated: 2025/10/07 08:53:13 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_meal_time(t_philo *p)
{
	pthread_mutex_lock(&p->meal_mtx);
	p->last_meal_ms = now_ms();
	pthread_mutex_unlock(&p->meal_mtx);
}

static void	initial_stagger(t_philo *p)
{
	if (p->sim->n % 2 == 0)
	{
		if (p->id % 2 == 0)
			busy_sleep_ms(p->sim->t_eat);
	}
	else if (p->id % 2 == 0)
		usleep(500);
}

static int	one_cycle(t_philo *p)
{
	take_forks(p);
	if (get_stopped(p->sim))
	{
		drop_forks(p);
		return (1);
	}
	do_eat(p);
	drop_forks(p);
	do_sleep_think(p);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	init_meal_time(p);
	initial_stagger(p);
	while (!get_stopped(p->sim))
	{
		if (one_cycle(p))
			break ;
	}
	return (NULL);
}
