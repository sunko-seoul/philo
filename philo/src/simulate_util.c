/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 16:13:43 by sunko             #+#    #+#             */
/*   Updated: 2023/08/22 11:58:00 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	pick_up_fork(t_philo *philo)
{
	philo->info->fork_arr[philo->l_fork_idx] = 1;
	philo->info->fork_arr[philo->r_fork_idx] = 1;
}

void	put_down_fork(t_philo *philo)
{
	philo->info->fork_arr[philo->l_fork_idx] = 0;
	philo->info->fork_arr[philo->r_fork_idx] = 0;
	pthread_mutex_unlock(&philo->struct_mutex->fork[philo->l_fork_idx]);
	pthread_mutex_unlock(&philo->struct_mutex->fork[philo->r_fork_idx]);
}

int	test_one_fork(t_philo *philo)
{
	if (philo->l_fork_idx == philo->r_fork_idx)
	{
		if (print_take_fork(philo) == DIE)
			return (DIE);
	}
	return (LIVE);
}

void	update_eat_count(t_philo *philo)
{
	philo->eat_count += 1;
	if (philo->must_eat != 0 && philo->eat_count == philo->must_eat)
	{
		pthread_mutex_lock(philo->struct_mutex->count);
		philo->info->count_must_eat_philo += 1;
		pthread_mutex_unlock(philo->struct_mutex->count);
	}
}

int	sleep_odd_philo(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		usleep(100);
		if (print_thinking(philo) == DIE)
			return (DIE);
		return (LIVE);
	}
	else
		return (LIVE);
}
