/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:36 by melkhatr          #+#    #+#             */
/*   Updated: 2025/11/18 14:03:03 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

static int	parse_into(const char *s, long min, long *dst, const char *msg)
{
	long	tmp;

	if (ft_atoi(s, &tmp) || tmp < min)
		return (ft_putstr_fd(msg, 2), -1);
	*dst = tmp;
	return (0);
}

static int	check_limits(t_sim *sim)
{
	if (sim->n <= 0)
		return (ft_putstr_fd("Error: invalid number of philosophers\n", 2), -1);
	if (sim->t_die < 1 || sim->t_eat < 0 || sim->t_sleep < 0)
		return (ft_putstr_fd("Error: invalid time values\n", 2), -1);
	if (sim->must_eat == 0)
		return (ft_putstr_fd("Error: must_eat cannot be 0\n", 2), -1);
	return (0);
}

int	parse_args(int ac, char **av, t_sim *sim)
{
	long	tmp;

	ft_bzero(sim, sizeof(*sim));
	if (ac != 5 && ac != 6)
		return (ft_putstr_fd("Usage: n t_die t_eat t_sleep[must_eat]\n", 2),
			-1);
	if (parse_into(av[1], 1, &tmp, "Error\n"))
		return (-1);
	sim->n = (int)tmp;
	if (parse_into(av[2], 0, &sim->t_die, "Error\n"))
		return (-1);
	if (parse_into(av[3], 0, &sim->t_eat, "Error\n"))
		return (-1);
	if (parse_into(av[4], 0, &sim->t_sleep, "Error\n"))
		return (-1);
	sim->must_eat = -1;
	if (ac == 6)
	{
		if (ft_atoi(av[5], &tmp))
			return (ft_putstr_fd("Error\n", 2), -1);
		sim->must_eat = (int)tmp;
	}
	return (check_limits(sim));
}
