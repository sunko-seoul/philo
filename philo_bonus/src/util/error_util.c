/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:13:09 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 16:13:38 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"
#define INT_MAX		2147483647

int	argc_error(void)
{
	write(2, "philo: argument count error.\n", 30);
	exit(EXIT_FAILURE);
	return (1);
}

int	malloc_error(void)
{
	write(2, "malloc: cannot heap memory arrocate.\n", 38);
	exit(EXIT_FAILURE);
	return (1);
}

int	argv_error(void)
{
	write(2, "philo: The value of argv must be greater than 0.\n", 50);
	exit(EXIT_FAILURE);
	return (1);
}
