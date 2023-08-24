/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:15:19 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 17:09:40 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_info(t_info *info, int argc, char *argv[])
{
	memset(info, 0, sizeof(t_info));
	info->num_of_philo = ft_atoi(argv[NUM_OF_PHILO]);
	info->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	info->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	info->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[NUM_OF_MUST_EAT]);
	info->pid_arr = (pid_t *)malloc(sizeof(pid_t) * info->num_of_philo);
	if (!info->pid_arr)
		return (ERROR);
	memset(info->pid_arr, 0, sizeof(pid_t) * info->num_of_philo);
	info->init_time = current_elapsed_time(0);
	info->s_semapo = malloc_parent_semapo(info->num_of_philo);
	if (!info->s_semapo)
	{
		free(info->pid_arr);
		return (ERROR);
	}
	return (SUCCESS);
}

int	init_unlink(void)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	return (0);
}
