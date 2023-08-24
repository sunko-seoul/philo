/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:12:13 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 21:04:58 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_die_flag(t_info *info)
{
	pthread_mutex_lock(info->struct_mutex->die);
	if (info->die_flag == 1)
	{
		pthread_mutex_unlock(info->struct_mutex->die);
		return (DIE);
	}
	pthread_mutex_unlock(info->struct_mutex->die);
	return (LIVE);
}

int	check_philo_elapsed_time(t_info *info)
{
	int		i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		pthread_mutex_lock(info->struct_mutex->time);
		info->philo_arr[i].elapsed_time = \
		current_elapsed_time(info->philo_arr[i].entry_time);
		if (info->philo_arr[i].elapsed_time >= info->time_to_die)
		{
			print_die(&(info->philo_arr[i]));
			pthread_mutex_lock(info->struct_mutex->die);
			info->die_flag = 1;
			pthread_mutex_unlock(info->struct_mutex->die);
			pthread_mutex_unlock(info->struct_mutex->time);
			return (DIE);
		}
		pthread_mutex_unlock(info->struct_mutex->time);
	}
	return (LIVE);
}

void	*simulate(void *temp)
{
	t_philo	*philo;
	int		flag;

	philo = (t_philo *)temp;
	if (sleep_odd_philo(philo) == DIE)
		return (NULL);
	while (1)
	{
		if (check_die_flag(philo->info) == DIE)
			return (NULL);
		flag = test_eat(philo);
		if (flag == DIE)
			return (NULL);
		else if (flag == EAT)
		{
			if (print_sleeping(philo) == DIE)
				return (NULL);
			goto_sleep(philo);
			if (print_thinking(philo) == DIE)
				return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	create_thread(t_info *info)
{
	int		i;

	i = 0;
	info->init_time = current_elapsed_time(0);
	while (i < info->num_of_philo)
	{
		info->philo_arr[i].entry_time = current_elapsed_time(0);
		pthread_create((info->philo_arr[i].pthread_id), NULL, \
		simulate, &(info->philo_arr[i]));
		i++;
	}
	while (1)
	{
		if (check_philo_elapsed_time(info) == DIE || \
		check_must_eat_philo(info) == DIE)
			break ;
		usleep(100);
	}
	i = 0;
	while (i < info->num_of_philo)
	{
		pthread_join(*info->philo_arr[i].pthread_id, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	*info;

	if (argc != 5 && argc != 6)
		return (argc_error());
	info = malloc_info();
	if (!info)
		return (malloc_error());
	if (!init_info(info, argc, argv))
		return (malloc_error());
	if (is_info_error(info, argc))
		return (argv_error());
	if (create_thread(info))
		return (malloc_error());
	clean_and_destroy(info);
	free(info);
}
