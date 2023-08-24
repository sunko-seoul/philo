/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:48:35 by sunko             #+#    #+#             */
/*   Updated: 2023/08/18 16:46:45 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

long long	current_elapsed_time(long long initial)
{
	struct timeval		tv;
	long long			current_time;

	gettimeofday(&tv, NULL);
	current_time = \
	(long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
	return (current_time - initial);
}

long long	get_print_time(t_info *info)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
	time -= info->init_time;
	return (time);
}
