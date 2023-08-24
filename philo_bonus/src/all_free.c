/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:41:43 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 17:41:34 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	child_semapo_all_free(t_philo *philo)
{
	if (sem_close(philo->s_semapo->flag))
		exit(EXIT_FAILURE);
	if (sem_unlink(philo->flag_name))
		exit(EXIT_FAILURE);
	if (sem_close(philo->s_semapo->time))
		exit(EXIT_FAILURE);
	if (sem_unlink(philo->time_name))
		exit(EXIT_FAILURE);
	if (sem_close(philo->s_semapo->count))
		exit(EXIT_FAILURE);
	if (sem_unlink(philo->count_name))
		exit(EXIT_FAILURE);
	free(philo->count_name);
	free(philo->time_name);
	free(philo->flag_name);
}

void	simulate_sem_close(t_philo *philo)
{
	if (sem_close(philo->s_semapo->flag))
		exit(EXIT_FAILURE);
	if (sem_unlink(philo->flag_name))
		exit(EXIT_FAILURE);
	if (sem_close(philo->s_semapo->time))
		exit(EXIT_FAILURE);
	if (sem_unlink(philo->time_name))
		exit(EXIT_FAILURE);
	if (sem_close(philo->s_semapo->count))
		exit(EXIT_FAILURE);
	if (sem_unlink(philo->count_name))
		exit(EXIT_FAILURE);
}

void	info_all_free(t_info *info, t_semapo *s_sema, pid_t *pid_arr)
{
	if (info)
		free(info);
	if (s_sema)
		free(s_sema);
	if (pid_arr)
		free(pid_arr);
	return ;
}

int	fork_all_free(t_info *info)
{
	int		i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		child_semapo_all_free(info->philo_arr[i]);
		free(info->philo_arr[i]);
	}
	free(info->philo_arr);
	fork_error(info);
	return (ERROR);
}

void	*child_semapo_option_free(t_philo *philo, int option)
{
	if (option == 0)
	{
		if (sem_close(philo->s_semapo->time))
			exit(EXIT_FAILURE);
		if (sem_unlink(philo->time_name))
			exit(EXIT_FAILURE);
		free(philo->count_name);
		free(philo->time_name);
		free(philo->flag_name);
	}
	else if (option == 1)
	{
		if (sem_close(philo->s_semapo->time))
			exit(EXIT_FAILURE);
		if (sem_unlink(philo->time_name))
			exit(EXIT_FAILURE);
		if (sem_close(philo->s_semapo->count))
			exit(EXIT_FAILURE);
		if (sem_unlink(philo->count_name))
			exit(EXIT_FAILURE);
		free(philo->count_name);
		free(philo->time_name);
		free(philo->flag_name);
	}
	return (NULL);
}
