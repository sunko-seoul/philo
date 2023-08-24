/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:14:03 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 21:04:47 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# define NUM_OF_PHILO		1
# define TIME_TO_DIE		2
# define TIME_TO_EAT		3
# define TIME_TO_SLEEP		4
# define NUM_OF_MUST_EAT	5
# define LIVE				0
# define DIE				1
# define EAT				2
# define NOT_EAT			3

typedef struct s_philo	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*die;
	pthread_mutex_t	*time;
	pthread_mutex_t	*count;
}	t_mutex;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				count_must_eat_philo;
	int				die_flag;
	int				*fork_arr;
	long long		init_time;
	t_mutex			*struct_mutex;
	struct s_philo	*philo_arr;
}	t_info;

typedef struct s_philo
{
	int					id;
	int					l_fork_idx;
	int					r_fork_idx;
	int					l_philo_idx;
	int					r_philo_idx;
	int					eat_count;
	int					must_eat;
	long long			entry_time;
	long long			elapsed_time;
	pthread_t			*pthread_id;
	t_info				*info;
	t_mutex				*struct_mutex;
}	t_philo;

/* util/atoi.c */
size_t			ft_strlen(const char *s);
int				is_space(char c);
int				ft_atoi(const char *str);

/* util/error.c */
int				argc_error(void);
int				malloc_error(void);
int				argv_error(void);
int				is_info_error(t_info *info, int argc);

/* print.c */
int				print_take_fork(t_philo *philo);
int				print_eating(t_philo *philo);
int				print_sleeping(t_philo *philo);
int				print_thinking(t_philo *philo);
int				print_die(t_philo *philo);

/* util/get_idx.c */
int				get_l_idx(t_info *info, int id);
int				get_r_idx(t_info *info, int id);
int				get_l_fork(t_info *info, int id);
int				get_r_fork(t_info *info, int id);

/* util/malloc.c */
int				init_info(t_info *info, int argc, char *argv[]);
t_info			*malloc_info(void);
t_philo			*malloc_philo_arr(int num_of_philo, t_info *info);
pthread_mutex_t	*malloc_mutex(int size);
t_mutex			*malloc_struct_mutex(int num_of_philo);

/* util/time.c */
long long		current_elapsed_time(long long initial);
long long		get_print_time(t_info *info);

/* main.c */
int				check_die_flag(t_info *info);
int				check_philo_elapsed_time(t_info *info);
void			*simulate(void *temp);
int				create_thread(t_info *info);

/* simulate.c */
int				goto_sleep(t_philo *philo);
int				goto_eat(t_philo *philo);
int				check_must_eat_philo(t_info *info);
int				test_eat(t_philo *philo);

/* simulate_util.c */
void			pick_up_fork(t_philo *philo);
void			put_down_fork(t_philo *philo);
int				test_one_fork(t_philo *philo);
void			update_eat_count(t_philo *philo);
int				sleep_odd_philo(t_philo *philo);

/* moniter.c */
void			all_free(t_mutex *struct_mutex, t_info *info);
int				clean_and_destroy(t_info *info);

#endif
