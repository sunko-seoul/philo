/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moniter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:45:39 by sunko             #+#    #+#             */
/*   Updated: 2023/08/21 10:28:17 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	all_free(t_mutex *struct_mutex, t_info *info)
{
	free(struct_mutex->count);
	free(struct_mutex->print);
	free(struct_mutex->time);
	free(struct_mutex->die);
	free(struct_mutex->fork);
	free(struct_mutex);
	free(info->philo_arr);
	free(info->fork_arr);
}

int	clean_and_destroy(t_info *info)
{
	t_mutex	*struct_mutex;
	int		i;

	i = -1;
	struct_mutex = info->struct_mutex;
	while (++i < info->num_of_philo)
	{
		pthread_mutex_destroy(&struct_mutex->fork[i]);
		free(info->philo_arr[i].pthread_id);
	}
	pthread_mutex_destroy(struct_mutex->count);
	pthread_mutex_destroy(struct_mutex->print);
	pthread_mutex_destroy(struct_mutex->time);
	pthread_mutex_unlock(struct_mutex->die);
	pthread_mutex_destroy(struct_mutex->die);
	all_free(struct_mutex, info);
	return (0);
}
