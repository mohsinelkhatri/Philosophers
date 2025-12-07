/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 08:50:43 by melkhatr          #+#    #+#             */
/*   Updated: 2025/11/18 14:02:59 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_sim	sim;

	if (parse_args(ac, av, &sim) != 0)
		return (1);
	if (sim_init(&sim) != 0)
		return (1);
	if (start_threads(&sim) != 0)
	{
		destroy_sim(&sim);
		return (1);
	}
	cleanup_and_join(&sim);
	destroy_sim(&sim);
	return (0);
}
