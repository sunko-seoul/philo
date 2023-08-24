/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunko <sunko@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 17:11:19 by sunko             #+#    #+#             */
/*   Updated: 2023/08/23 21:58:51 by sunko            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdio.h>
# include <signal.h>
# define SUCCESS			0
# define ERROR				1
# define NUM_OF_PHILO		1
# define TIME_TO_DIE		2
# define TIME_TO_EAT		3
# define TIME_TO_SLEEP		4
# define NUM_OF_MUST_EAT	5
# define LIVE				0
# define DIE				1
# define EAT				2
# define NOT_EAT			3
# define EAT				2
# define SLEEP				3
# define THINK				4
# define TAKE_FORK			5
# define SEM_DIE			"sem_die"
# define SEM_FORK			"sem_fork"
# define SEM_PRINT			"sem_print"

typedef struct s_philo	t_philo;

typedef struct s_semapo
{
	sem_t	*fork;
	sem_t	*print;
	sem_t	*time;
	sem_t	*count;
	sem_t	*flag;
}	t_semapo;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				count_must_eat_philo;
	int				die_flag;
	long long		init_time;
	pid_t			*pid_arr;
	t_semapo		*s_semapo;
	t_philo			**philo_arr;
}	t_info;

typedef struct s_philo
{
	int					id;
	int					die_flag;
	int					eat_count;
	int					must_eat;
	long long			entry_time;
	long long			elapsed_time;
	pthread_t			*thread_id;
	t_info				*info;
	t_semapo			*s_semapo;
	char				*flag_name;
	char				*time_name;
	char				*count_name;
}	t_philo;

/* error_util.c */
int				argc_error(void);
int				malloc_error(void);
int				argv_error(void);

/* error.c */
int				fork_error(t_info *info);
int				is_info_error(t_info *info, int argc);
int				kill_malloc_error(t_info *info);
int				killer_error(t_info *info);

/* ft_atoi.c */
size_t			ft_strlen(const char *s);
int				is_space(char c);
int				ft_atoi(const char *str);

/* ft_strjoin.c */
char			*ft_strjoin(char const *s1, char const *s2);

/* ft_itoa.c */
char			*ft_itoa(int n);

/* malloc.c */
t_info			*malloc_info(void);
pthread_mutex_t	*malloc_mutex(int size);
t_semapo		*malloc_parent_semapo(int num_of_philo);
t_semapo		*malloc_child_semapo(t_philo *philo);

/* malloc_util.c */
t_philo			*malloc_philo(t_info *info);
t_philo			**malloc_philo_arr(t_info *info);

/* sem_print.c */
long long		current_elapsed_time(long long initial);
int				sem_print(t_philo *philo, int mode);

/* init.c */
int				init_info(t_info *info, int argc, char *argv[]);
int				init_unlink(void);

/* simulate_util.c */
int				goto_sleep(t_philo *philo);
int				goto_eat(t_philo *philo);
int				test_one_fork(t_philo *philo);

/* simulate.c */
int				simulate(t_philo *philo);
int				check_die_flag(t_philo *philo);
long long		get_time(t_philo *philo, long long time);
int				wait_and_kill(t_info *info);
void			*moniter_thread(void *v_philo);
int				check_must_eat_count(t_philo *philo);
int				check_philo_elapsed_time(t_philo *philo);

/* all_free.c */
void			child_semapo_all_free(t_philo *philo);
void			info_all_free(t_info *info, t_semapo *s_sema, pid_t *pid_arr);
int				fork_all_free(t_info *info);
void			simulate_sem_close(t_philo *philo);
void			*child_semapo_option_free(t_philo *philo, int option);

#endif
