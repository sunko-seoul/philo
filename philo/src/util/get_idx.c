/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_idx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 00:03:02 by sunko             #+#    #+#             */
/*   Updated: 2023/08/18 16:32:12 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	get_l_idx(t_info *info, int id)
{
	int		l_philo;

	l_philo = (id - 1 + info->num_of_philo) % info->num_of_philo;
	return (l_philo);
}

int	get_r_idx(t_info *info, int id)
{
	int		r_philo;

	r_philo = (id + 1) % info->num_of_philo;
	return (r_philo);
}

int	get_l_fork(t_info *info, int id)
{
	int		l_fork;

	l_fork = (id - 1 + info->num_of_philo) % info->num_of_philo;
	return (l_fork);
}

int	get_r_fork(t_info *info, int id)
{
	int		r_fork;

	r_fork = (id) % info->num_of_philo;
	return (r_fork);
}
