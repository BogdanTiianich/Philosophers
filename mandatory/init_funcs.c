/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:30:01 by hbecki            #+#    #+#             */
/*   Updated: 2022/05/12 21:07:47 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_rules	*init_rules(int argc, char **argv)
{
	t_rules		*rules;
	t_timeval	time;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (rules == NULL)
	{
		ft_errors(1);
	}
	if (ft_check_args(argc, argv) == -1)
		ft_errors(2);
	rules->number_of_phils = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	gettimeofday(&time, NULL);
	rules->start_time = time;
	if (argc == 6)
		rules->im_full_times = ft_atoi(argv[5]);
	else
		rules->im_full_times = -1;
	return (rules);
}

void	ft_init_game(t_data **data, t_rules *rules, \
pthread_mutex_t **avail_forks, int i)
{
	t_timeval		curr;

	data[i] = (t_data *)malloc(sizeof(t_data));
	ft_check_malloc(data[i]);
	(*data[i]).avail_forks = avail_forks;
	(*data[i]).rules = rules;
	(*data[i]).philos = (t_philos *)malloc(sizeof(t_philos));
	ft_check_malloc((*data[i]).philos);
	if (gettimeofday(&curr, NULL) != 0)
		ft_errors(0);
	(*data[i]).philos->number = i;
	(*data[i]).philos->last_dinner_time = curr;
	(*data[i]).philos->alive = 1;
	(*data[i]).philos->forks_i_need = (int *)malloc(sizeof(int) * 2);
	ft_check_malloc((*data[i]).philos->forks_i_need);
	ft_define_forks_i_need((*data[i]).philos, rules->number_of_phils);
}

void	ft_forks_init(pthread_mutex_t *avail_forks, int number_of_phils)
{
	t_vars		vars;

	vars.i = 0;
	while (vars.i < number_of_phils)
	{
		if (pthread_mutex_init(&avail_forks[vars.i], NULL) != 0)
			ft_errors(0);
		vars.i++;
	}
}
