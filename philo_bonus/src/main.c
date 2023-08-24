/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:17:06 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 22:00:28 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_philo(t_info *info)
{
	int		i;
	int		j;
	t_philo	*philo;

	i = -1;
	j = -1;
	info->init_time = current_elapsed_time(0);
	info->philo_arr = malloc_philo_arr(info);
	if (!(info->philo_arr))
		return (ERROR);
	while (++i < info->num_of_philo)
		info->philo_arr[i]->entry_time = info->init_time;
	i = -1;
	while (++i < info->num_of_philo)
	{
		philo = info->philo_arr[i];
		info->pid_arr[i] = fork();
		if (info->pid_arr[i] < 0)
			return (fork_all_free(info));
		else if (info->pid_arr[i] == 0)
			simulate(philo);
	}
	return (SUCCESS);
}

int	wait_and_kill(t_info *info)
{
	pid_t		pid;
	int			i;

	i = -1;
	pid = waitpid(-1, 0, 0);
	while (++i < info->num_of_philo)
		kill(info->pid_arr[i], SIGTERM);
	sem_close(info->s_semapo->print);
	sem_close(info->s_semapo->fork);
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_info	*info;

	if (argc != 5 && argc != 6)
		return (argc_error());
	init_unlink();
	info = malloc_info();
	if (!info)
		return (malloc_error());
	if (init_info(info, argc, argv))
	{
		free(info);
		return (malloc_error());
	}
	if (is_info_error(info, argc))
	{
		info_all_free(info, info->s_semapo, info->pid_arr);
		return (argv_error());
	}
	if (create_philo(info))
	{
		info_all_free(info, info->s_semapo, info->pid_arr);
		return (killer_error(info));
	}
	wait_and_kill(info);
}
