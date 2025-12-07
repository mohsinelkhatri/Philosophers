/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkhatr <melkhatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 08:51:18 by melkhatr          #+#    #+#             */
/*   Updated: 2025/10/22 09:59:13 by melkhatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static const char	*skip_ws(const char *s)
{
	while (is_space(*s))
		s++;
	return (s);
}

static int	take_sign(const char **ps, long *sign)
{
	const char	*s;

	s = *ps;
	*sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			*sign = -1;
		s++;
	}
	if (!is_digit(*s))
		return (1);
	*ps = s;
	return (0);
}

int	ft_atoi(const char *s, long *out)
{
	long	sign;
	long	val;

	if (!s || !*s)
		return (1);
	s = skip_ws(s);
	if (!*s)
		return (1);
	if (take_sign(&s, &sign))
		return (1);
	val = 0;
	while (is_digit(*s))
	{
		val = val * 10 + (*s - '0');
		if (val * sign > INT_MAX || val * sign < INT_MIN)
			return (1);
		s++;
	}
	if (*s != '\0')
		return (1);
	*out = val * sign;
	return (0);
}
