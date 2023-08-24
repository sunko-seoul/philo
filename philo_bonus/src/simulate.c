/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:16:10 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 21:36:15 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_fork(t_philo *philo)
{
	if (sem_wait(philo->s_semapo->fork))
		exit(EXIT_FAILURE);
	if (sem_print(philo, TAKE_FORK) == DIE)
		return (DIE);
	if (sem_wait(philo->s_semapo->fork))
		exit(EXIT_FAILURE);
	if (sem_print(philo, TAKE_FORK) == DIE)
		return (DIE);
	return (LIVE);
}

void	down_fork(t_philo *philo)
{
	if (sem_post(philo->s_semapo->fork))
		exit(EXIT_FAILURE);
	if (sem_post(philo->s_semapo->fork))
		exit(EXIT_FAILURE);
}

int	simulate_core(t_philo *philo)
{
	while (1)
	{
		if (check_die_flag(philo) == DIE || \
		test_one_fork(philo) == DIE)
			break ;
		if (get_fork(philo) == DIE)
			break ;
		if (sem_print(philo, EAT) == DIE)
			break ;
		sem_wait(philo->s_semapo->time);
		philo->entry_time = current_elapsed_time(0);
		sem_post(philo->s_semapo->time);
		goto_eat(philo);
		down_fork(philo);
		if (sem_print(philo, SLEEP) == DIE)
			break ;
		goto_sleep(philo);
		if (sem_print(philo, THINK) == DIE)
			break ;
		usleep(100);
	}
	sem_print(philo, DIE);
	return (SUCCESS);
}

int	simulate(t_philo *philo)
{
	if (pthread_create(philo->thread_id, NULL, moniter_thread, (void *)philo))
		exit(EXIT_FAILURE);
	simulate_core(philo);
	if (pthread_join(*philo->thread_id, NULL))
		exit(EXIT_FAILURE);
	simulate_sem_close(philo);
	exit(EXIT_SUCCESS);
}
