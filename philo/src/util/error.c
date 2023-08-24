/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:27:44 by sunko             #+#    #+#             */
/*   Updated: 2023/08/18 16:47:54 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	argc_error(void)
{
	write(2, "philo: argument count error.\n", 30);
	return (1);
}

int	malloc_error(void)
{
	write(2, "malloc: cannot heap memory arrocate.\n", 38);
	return (1);
}

int	argv_error(void)
{
	write(2, "philo: The value of argv must be greater than 0.\n", 50);
	return (1);
}

int	is_info_error(t_info *info, int argc)
{
	if (info->num_of_philo <= 0 \
	|| info->time_to_die <= 0 \
	|| info->time_to_eat <= 0 \
	|| info->time_to_sleep <= 0 \
	|| (argc == 6 && info->num_of_must_eat <= 0))
	{
		return (1);
	}
	return (0);
}
