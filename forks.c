/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:50:34 by melkhatr          #+#    #+#             */
/*   Updated: 2025/10/22 09:42:42 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single(t_philo *p)
{
	t_sim	*sim;

	sim = p->sim;
	pthread_mutex_lock(&sim->forks[p->left]);
	print_state(sim, p->id, "has taken a fork", 0);
	while (!get_stopped(sim))
		usleep(200);
	pthread_mutex_unlock(&sim->forks[p->left]);
}

static void	lock_left_right(t_philo *p)
{
	pthread_mutex_lock(&p->sim->forks[p->left]);
	print_state(p->sim, p->id, "has taken a fork", 0);
	pthread_mutex_lock(&p->sim->forks[p->right]);
	print_state(p->sim, p->id, "has taken a fork", 0);
}

static void	lock_right_left(t_philo *p)
{
	pthread_mutex_lock(&p->sim->forks[p->right]);
	print_state(p->sim, p->id, "has taken a fork", 0);
	pthread_mutex_lock(&p->sim->forks[p->left]);
	print_state(p->sim, p->id, "has taken a fork", 0);
}

void	take_forks(t_philo *p)
{
	t_sim	*sim;

	sim = p->sim;
	if (sim->n == 1)
	{
		handle_single(p);
		return ;
	}
	room_enter(sim);
	if (p->id % 2 == 1)
		lock_left_right(p);
	else
		lock_right_left(p);
}

void	drop_forks(t_philo *p)
{
	if (p->sim->n == 1 || p->left == p->right)
		return ;
	if (p->id % 2 == 1)
	{
		pthread_mutex_unlock(&p->sim->forks[p->right]);
		pthread_mutex_unlock(&p->sim->forks[p->left]);
	}
	else
	{
		pthread_mutex_unlock(&p->sim->forks[p->left]);
		pthread_mutex_unlock(&p->sim->forks[p->right]);
	}
	room_leave(p->sim);
}
