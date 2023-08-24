/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:20:09 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 16:49:08 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#define INT_MAX		2147483647

void	child_kill(t_info *info)
{
	int		i;

	i = -1;
	while (++i < info->num_of_philo)
	{
		if (info->pid_arr[i] == 0)
			break ;
		if (kill(info->pid_arr[i], SIGTERM))
		{
			write(2, "kill: kill error\n", 18);
			exit(EXIT_FAILURE);
		}
	}
	return ;
}

int	fork_error(t_info *info)
{
	child_kill(info);
	write(2, "fork: failed fork\n", 19);
	exit(EXIT_FAILURE);
}

int	kill_malloc_error(t_info *info)
{
	child_kill(info);
	malloc_error();
	exit(EXIT_FAILURE);
}

int	killer_error(t_info *info)
{
	child_kill(info);
	write(2, "philo_bonus: error\n", 20);
	exit(EXIT_FAILURE);
}

int	is_info_error(t_info *info, int argc)
{
	if ((info->num_of_philo <= 0 || info->num_of_philo > 1000) \
	|| (info->time_to_die <= 0 || info->time_to_die > INT_MAX) \
	|| (info->time_to_eat <= 0 || info->time_to_eat > INT_MAX) \
	|| (info->time_to_sleep <= 0 || info->time_to_sleep > INT_MAX) \
	|| (argc == 6 \
	&& (info->num_of_must_eat <= 0 || info->num_of_must_eat > INT_MAX)))
	{
		return (1);
	}
	return (0);
}
