/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:16:24 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/26 21:48:05 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>//gettimeday
# include <stdlib.h>//malloc
# include <string.h> // Для strerror
# include <errno.h> /* содержит объявления для errno */

typedef struct timeval	t_timeval;
typedef struct s_rules{
	int			number_of_phils;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			im_full_times;
	t_timeval	start_time;
}	t_rules;
typedef struct s_philos{
	t_timeval	last_dinner_time;
	int			alive;
	int			*forks_i_need;
	int			number;
}	t_philos;
typedef struct s_data{
	t_philos		*philos;
	t_rules			*rules;
	pthread_mutex_t	*mutex;
	int				**avail_forks;
}	t_data;
typedef struct s_vars
{
	int		i;
	int		j;
	int		count;
	int		counter;
	int		argc;

	char	**argv;
	char	**envp;
	char	**s;
}	t_vars;

int		ft_isnumber(char *str);
int		ft_check_args(int argc, char **argv);
int		ft_atoi(const char *s);
void	ft_putstr_fd(char *s, int fd);
long	ft_time_diff_from_now_ms(t_timeval t1);
long	ft_time_from_start(t_timeval t);
t_rules	*init_rules(int argc, char **argv);
void	ft_init_game(t_data **data, t_rules *rules, int **avail_forks, int i);
void	ft_forks_init(int *avail_forks, int number_of_phils);
void	ft_errors(int code);
void	ft_free(void **pointer);
void	ft_check_malloc(void *data);
int		ft_check_if_dead(t_data data);
int		waiting_for_forks(t_data data);
int		ft_philo_eating(t_data data);
int		ft_philo_sleeping(t_data data);
int		ft_start_dinning(t_data data);
void	*philos_life(void *data);
void	ft_define_forks_i_need(t_philos *philos, int number_of_philos);
void	ft_run_game(t_data **data, pthread_t \
*threads, t_rules *rules, int **avail_forks);
#endif