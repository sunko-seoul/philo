/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:28:43 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 21:55:15 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_die_flag(t_philo *philo)
{
	sem_wait(philo->s_semapo->flag);
	if (philo->die_flag == 1)
	{
		sem_post(philo->s_semapo->flag);
		return (DIE);
	}
	sem_post(philo->s_semapo->flag);
	return (LIVE);
}

int	check_philo_elapsed_time(t_philo *philo)
{
	long long	die_time;
	long long	elapsed_time;
	long long	entry_time;

	sem_wait(philo->s_semapo->time);
	die_time = philo->info->time_to_die;
	entry_time = philo->entry_time;
	sem_post(philo->s_semapo->time);
	elapsed_time = current_elapsed_time(entry_time);
	if (die_time <= elapsed_time)
	{
		sem_print(philo, DIE);
		sem_wait(philo->s_semapo->flag);
		philo->die_flag = 1;
		sem_post(philo->s_semapo->flag);
		return (DIE);
	}
	return (LIVE);
}

int	check_must_eat_count(t_philo *philo)
{
	sem_wait(philo->s_semapo->count);
	if (philo->info->num_of_must_eat != 0 && \
	philo->info->num_of_must_eat == philo->eat_count)
	{
		sem_wait(philo->s_semapo->flag);
		philo->die_flag = 1;
		sem_post(philo->s_semapo->flag);
		sem_post(philo->s_semapo->count);
		return (DIE);
	}
	sem_post(philo->s_semapo->count);
	return (LIVE);
}

void	*moniter_thread(void *v_philo)
{
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	while (1)
	{
		if (check_must_eat_count(philo) == DIE)
			break ;
		if (check_philo_elapsed_time(philo) == DIE)
			break ;
		usleep(100);
	}
	return (NULL);
}
