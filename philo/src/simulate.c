/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 23:13:09 by sunko             #+#    #+#             */
/*   Updated: 2023/08/24 11:37:58 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	goto_sleep(t_philo *philo)
{
	long long	sleep_time;
	long long	entry_time;

	sleep_time = philo->info->time_to_sleep * 100;
	entry_time = current_elapsed_time(0);
	while (1)
	{
		if (sleep_time < 100)
			sleep_time = 100;
		else
			sleep_time /= 2;
		usleep(sleep_time);
		if (current_elapsed_time(entry_time) >= philo->info->time_to_sleep)
			break ;
	}
	return (0);
}

int	goto_eat(t_philo *philo)
{
	long long	sleep_time;
	long long	entry_time;

	sleep_time = philo->info->time_to_eat * 100;
	entry_time = current_elapsed_time(0);
	while (1)
	{
		if (sleep_time < 100)
			sleep_time = 100;
		else
			sleep_time /= 2;
		usleep(100);
		if (current_elapsed_time(entry_time) >= philo->info->time_to_eat)
			break ;
	}
	update_eat_count(philo);
	return (0);
}

int	check_must_eat_philo(t_info *info)
{
	pthread_mutex_lock(info->struct_mutex->count);
	if (info->count_must_eat_philo == info->num_of_philo)
	{
		pthread_mutex_lock(info->struct_mutex->die);
		info->die_flag = 1;
		pthread_mutex_unlock(info->struct_mutex->die);
		pthread_mutex_unlock(info->struct_mutex->count);
		return (DIE);
	}
	pthread_mutex_unlock(info->struct_mutex->count);
	return (LIVE);
}

int	test_eat(t_philo *philo)
{
	if (test_one_fork(philo) == DIE)
		return (DIE);
	pthread_mutex_lock(&philo->struct_mutex->fork[philo->l_fork_idx]);
	pthread_mutex_lock(&philo->struct_mutex->fork[philo->r_fork_idx]);
	if (philo->info->fork_arr[philo->l_fork_idx] == 0 && \
	philo->info->fork_arr[philo->r_fork_idx] == 0)
	{
		pthread_mutex_lock(philo->struct_mutex->time);
		philo->entry_time = current_elapsed_time(0);
		pthread_mutex_unlock(philo->struct_mutex->time);
		pick_up_fork(philo);
		if (print_take_fork(philo) == DIE || \
		print_take_fork(philo) == DIE || \
		print_eating(philo) == DIE)
		{
			put_down_fork(philo);
			return (DIE);
		}
		goto_eat(philo);
		put_down_fork(philo);
		return (EAT);
	}
	pthread_mutex_unlock(&philo->struct_mutex->fork[philo->l_fork_idx]);
	pthread_mutex_unlock(&philo->struct_mutex->fork[philo->r_fork_idx]);
	return (NOT_EAT);
}
