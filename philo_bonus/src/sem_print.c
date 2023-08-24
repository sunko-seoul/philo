/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 23:40:33 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 14:51:03 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	get_time(t_philo *philo, long long time)
{
	long long	time_stamp;

	sem_wait(philo->s_semapo->time);
	time_stamp = current_elapsed_time(time);
	sem_post(philo->s_semapo->time);
	return (time_stamp);
}

long long	current_elapsed_time(long long initial)
{
	struct timeval		tv;
	long long			current_time;

	gettimeofday(&tv, NULL);
	current_time = \
	(long long)tv.tv_sec * 1000 + (long long)tv.tv_usec / 1000;
	return (current_time - initial);
}

int	sem_print(t_philo *philo, int mode)
{
	long long	time_stamp;

	if (check_die_flag(philo) == DIE)
		return (DIE);
	time_stamp = get_time(philo, philo->info->init_time);
	sem_wait(philo->s_semapo->print);
	if (mode == DIE)
	{
		printf("%lld %d died\n", time_stamp, philo->id + 1);
		return (DIE);
	}
	if (mode == EAT)
		printf("%lld %d is eating\n", time_stamp, philo->id + 1);
	else if (mode == SLEEP)
		printf("%lld %d is sleeping\n", time_stamp, philo->id + 1);
	else if (mode == THINK)
		printf("%lld %d is thinking\n", time_stamp, philo->id + 1);
	else if (mode == TAKE_FORK)
		printf("%lld %d has taken a fork\n", time_stamp, philo->id + 1);
	sem_post(philo->s_semapo->print);
	return (SUCCESS);
}
