/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:40:42 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 17:58:54 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

t_info	*malloc_info(void)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	return (info);
}

t_semapo	*malloc_parent_semapo(int num_of_philo)
{
	t_semapo	*s_semapo;

	s_semapo = (t_semapo *)malloc(sizeof(t_semapo));
	if (!s_semapo)
		return (NULL);
	s_semapo->fork = \
	sem_open(SEM_FORK, O_CREAT | O_EXCL, 0644, num_of_philo);
	if (s_semapo->fork == SEM_FAILED)
	{
		free(s_semapo);
		return (NULL);
	}
	s_semapo->print = \
	sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	if (s_semapo->print == SEM_FAILED)
	{
		sem_close(s_semapo->fork);
		sem_unlink(SEM_FORK);
		free(s_semapo);
		return (NULL);
	}
	return (s_semapo);
}

void	*option_free(t_philo *philo, int option)
{
	if (option == 1)
	{
		free(philo->count_name);
	}
	else if (option == 2)
	{
		free(philo->count_name);
		free(philo->time_name);
	}
	else if (option == 3)
	{
		free(philo->count_name);
		free(philo->time_name);
		free(philo->flag_name);
	}
	return (NULL);
}

void	*child_semapo_init(t_philo *philo, char *string)
{
	philo->count_name = ft_strjoin(string, "_count");
	if (!philo->count_name)
		return (NULL);
	philo->time_name = ft_strjoin(string, "_time");
	if (!philo->time_name)
		return (option_free(philo, 1));
	philo->flag_name = ft_strjoin(string, "_flag");
	if (!philo->flag_name)
		return (option_free(philo, 2));
	free(string);
	sem_unlink(philo->time_name);
	sem_unlink(philo->count_name);
	sem_unlink(philo->flag_name);
	return (NULL);
}

t_semapo	*malloc_child_semapo(t_philo *philo)
{
	char	*philo_id_string;

	philo_id_string = ft_itoa(philo->id);
	if (!philo_id_string)
		exit(EXIT_FAILURE);
	child_semapo_init(philo, philo_id_string);
	philo->s_semapo->time = \
	sem_open(philo->time_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->s_semapo->time == SEM_FAILED)
		return (option_free(philo, 3));
	philo->s_semapo->count = \
	sem_open(philo->count_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->s_semapo->count == SEM_FAILED)
		return (child_semapo_option_free(philo, 0));
	philo->s_semapo->flag = \
	sem_open(philo->flag_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->s_semapo->flag == SEM_FAILED)
		return (child_semapo_option_free(philo, 1));
	return (philo->s_semapo);
}
