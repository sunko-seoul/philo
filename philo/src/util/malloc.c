/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:43:56 by sunko             #+#    #+#             */
/*   Updated: 2023/08/19 23:27:23 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

int	init_info(t_info *info, int argc, char *argv[])
{
	memset(info, 0, sizeof(t_info));
	info->num_of_philo = ft_atoi(argv[NUM_OF_PHILO]);
	info->time_to_die = ft_atoi(argv[TIME_TO_DIE]);
	info->time_to_eat = ft_atoi(argv[TIME_TO_EAT]);
	info->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP]);
	if (argc == 6)
		info->num_of_must_eat = ft_atoi(argv[NUM_OF_MUST_EAT]);
	else
		info->num_of_must_eat = 0;
	info->count_must_eat_philo = 0;
	info->die_flag = 0;
	info->init_time = 0;
	info->fork_arr = (int *)malloc(sizeof(int) * info->num_of_philo);
	if (!info->fork_arr)
		return (0);
	info->struct_mutex = malloc_struct_mutex(info->num_of_philo);
	if (!info->struct_mutex)
		return (0);
	info->philo_arr = malloc_philo_arr(info->num_of_philo, info);
	if (!info->philo_arr)
		return (0);
	return (1);
}

t_info	*malloc_info(void)
{
	t_info	*new;

	new = (t_info *)malloc(sizeof(t_info));
	if (!new)
		return (NULL);
	return (new);
}

t_philo	*malloc_philo_arr(int num_of_philo, t_info *info)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(sizeof(t_philo) * num_of_philo);
	if (!philo)
		return (NULL);
	while (++i < num_of_philo)
	{
		philo[i].id = i;
		philo[i].l_fork_idx = get_l_fork(info, i);
		philo[i].r_fork_idx = get_r_fork(info, i);
		philo[i].l_philo_idx = get_l_idx(info, i);
		philo[i].r_philo_idx = get_r_idx(info, i);
		philo[i].must_eat = info->num_of_must_eat;
		philo[i].eat_count = 0;
		philo[i].entry_time = 0;
		philo[i].elapsed_time = 0;
		philo[i].info = info;
		philo[i].struct_mutex = info->struct_mutex;
		philo[i].pthread_id = (pthread_t *)malloc(sizeof(pthread_t));
		if (!philo->pthread_id)
			return (NULL);
	}
	return (philo);
}

pthread_mutex_t	*malloc_mutex(int size)
{
	pthread_mutex_t	*new;
	int				i;

	i = -1;
	new = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
	if (!new)
		return (NULL);
	while (++i < size)
		pthread_mutex_init(&new[i], NULL);
	return (new);
}

t_mutex	*malloc_struct_mutex(int num_of_philo)
{
	t_mutex	*struct_mutex;

	struct_mutex = (t_mutex *)malloc(sizeof(t_mutex));
	if (!struct_mutex)
		return (NULL);
	struct_mutex->print = malloc_mutex(1);
	if (!struct_mutex->print)
		return (NULL);
	struct_mutex->fork = malloc_mutex(num_of_philo);
	if (!struct_mutex->fork)
		return (NULL);
	struct_mutex->count = malloc_mutex(1);
	if (!struct_mutex->count)
		return (NULL);
	struct_mutex->die = malloc_mutex(1);
	if (!struct_mutex->die)
		return (NULL);
	struct_mutex->time = malloc_mutex(1);
	if (!struct_mutex->time)
		return (NULL);
	return (struct_mutex);
}
