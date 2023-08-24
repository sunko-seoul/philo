/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 00:19:06 by sunko             #+#    #+#             */
/*   Updated: 2023/08/18 16:49:38 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_take_fork(t_philo *philo)
{
	t_mutex		*struct_mutex;
	long long	time_stamp;

	struct_mutex = philo->struct_mutex;
	if (check_die_flag(philo->info) == DIE)
		return (DIE);
	time_stamp = get_print_time(philo->info);
	pthread_mutex_lock(struct_mutex->print);
	printf("%lld %d has taken a fork\n", time_stamp, philo->id + 1);
	pthread_mutex_unlock(struct_mutex->print);
	if (philo->l_fork_idx == philo->r_fork_idx)
		return (DIE);
	return (LIVE);
}

int	print_eating(t_philo *philo)
{
	t_mutex		*struct_mutex;
	long long	time_stamp;

	struct_mutex = philo->struct_mutex;
	if (check_die_flag(philo->info) == DIE)
		return (DIE);
	time_stamp = get_print_time(philo->info);
	pthread_mutex_lock(struct_mutex->print);
	printf("%lld %d is eating\n", time_stamp, philo->id + 1);
	pthread_mutex_unlock(struct_mutex->print);
	return (LIVE);
}

int	print_sleeping(t_philo *philo)
{
	t_mutex		*struct_mutex;
	long long	time_stamp;

	struct_mutex = philo->struct_mutex;
	if (check_die_flag(philo->info) == DIE)
		return (DIE);
	time_stamp = get_print_time(philo->info);
	pthread_mutex_lock(struct_mutex->print);
	printf("%lld %d is sleeping\n", time_stamp, philo->id + 1);
	pthread_mutex_unlock(struct_mutex->print);
	return (LIVE);
}

int	print_thinking(t_philo *philo)
{
	t_mutex		*struct_mutex;
	long long	time_stamp;

	struct_mutex = philo->struct_mutex;
	if (check_die_flag(philo->info) == DIE)
		return (DIE);
	time_stamp = get_print_time(philo->info);
	pthread_mutex_lock(struct_mutex->print);
	printf("%lld %d is thinking\n", time_stamp, philo->id + 1);
	pthread_mutex_unlock(struct_mutex->print);
	return (LIVE);
}

int	print_die(t_philo *philo)
{
	t_mutex		*struct_mutex;
	long long	time_stamp;

	struct_mutex = philo->struct_mutex;
	if (check_die_flag(philo->info) == DIE)
		return (DIE);
	time_stamp = get_print_time(philo->info);
	pthread_mutex_lock(struct_mutex->print);
	printf("%lld %d died\n", time_stamp, philo->id + 1);
	pthread_mutex_unlock(struct_mutex->print);
	return (LIVE);
}
