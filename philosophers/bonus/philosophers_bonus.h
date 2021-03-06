/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:16:24 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/26 21:43:03 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>//gettimeday
# include <stdlib.h>//malloc
# include <string.h> // Для strerror
# include <errno.h> /* содержит объявления для errno */
# include <semaphore.h>
# define SEMAPHORE_NAME "/SEMKA"

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
	int			number;
	int			id;
}	t_philos;
typedef struct s_data{
	t_philos	*philos;
	t_rules		*rules;
	sem_t		*semaphore;
	int			thinking_flag;
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
void	ft_init_game(t_data **data, t_rules *rules, sem_t *semaphore, int i);
void	ft_init_orig_structers(t_data ***data, \
t_rules **rules, sem_t **semaphore);
void	ft_errors(int code);
void	ft_free(void **pointer);
void	ft_check_malloc(void *data);
int		ft_philo_eating(t_data data);
int		ft_philo_sleeping(t_data data);
void	ft_print_thinking(void *data);
int		ft_start_dinning(t_data data);
int		philos_life(t_data *data);
int		ft_check_if_dead(t_data data);
void	ft_run_game(t_data **data, sem_t *semaphore, t_rules *rules);
int		ft_waiter(int num_of_processes, t_data **data);
#endif