/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:23:47 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 21:38:21 by sunko            ###   ########.fr       */
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
		usleep(sleep_time);
		if (current_elapsed_time(entry_time) >= philo->info->time_to_eat)
			break ;
	}
	if (sem_wait(philo->s_semapo->count))
		exit(EXIT_FAILURE);
	philo->eat_count += 1;
	if (sem_post(philo->s_semapo->count))
		exit(EXIT_FAILURE);
	return (0);
}

int	test_one_fork(t_philo *philo)
{
	if (philo->info->num_of_philo == 1)
	{
		sem_wait(philo->s_semapo->fork);
		sem_print(philo, TAKE_FORK);
		sem_post(philo->s_semapo->fork);
		return (DIE);
	}
	else
		return (LIVE);
}
