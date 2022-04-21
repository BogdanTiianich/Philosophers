/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:16:24 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/14 21:01:57 by hbecki           ###   ########.fr       */
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
#endif