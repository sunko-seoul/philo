/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:27:14 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 17:33:56 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

t_philo	*malloc_philo(t_info *info)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->must_eat = info->num_of_must_eat;
	philo->info = info;
	philo->thread_id = malloc(sizeof(pthread_t));
	if (!philo->thread_id)
	{
		free(philo);
		return (NULL);
	}
	philo->s_semapo = info->s_semapo;
	return (philo);
}

void	*malloc_philo_free(t_philo **philo_arr, int option, int index)
{
	int		i;

	i = 0;
	if (option == 0)
	{
		while (i < index)
		{
			free(philo_arr[i]);
			i++;
		}
		free(philo_arr);
	}
	else if (option == 1)
	{
		while (i < index)
		{
			child_semapo_all_free(philo_arr[i]);
			free(philo_arr[i]);
			i++;
		}
		free(philo_arr[i]);
		free(philo_arr);
	}
	return (NULL);
}

t_philo	**malloc_philo_arr(t_info *info)
{
	t_philo	**philo_arr;
	int		i;
	int		j;

	i = -1;
	j = 0;
	philo_arr = (t_philo **)malloc(sizeof(t_philo *) * info->num_of_philo);
	if (!philo_arr)
		return (NULL);
	while (++i < info->num_of_philo)
	{
		philo_arr[i] = malloc_philo(info);
		if (!(philo_arr[i]))
			return (malloc_philo_free(philo_arr, 0, i));
		philo_arr[i]->id = i;
		if (!malloc_child_semapo(philo_arr[i]))
			return (malloc_philo_free(philo_arr, 1, i));
	}
	return (philo_arr);
}
