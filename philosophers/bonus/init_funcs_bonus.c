/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:30:01 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/26 21:43:31 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_rules	*init_rules(int argc, char **argv)
{
	t_rules		*rules;
	t_timeval	time;

	rules = (t_rules *)malloc(sizeof(t_rules));
	ft_check_malloc(rules);
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

void	ft_init_game(t_data **data, t_rules *rules, sem_t *semaphore, int i)
{
	t_timeval		curr;

	data[i] = (t_data *)malloc(sizeof(t_data));
	ft_check_malloc(data[i]);
	(*data[i]).rules = rules;
	(*data[i]).philos = (t_philos *)malloc(sizeof(t_philos));
	ft_check_malloc((*data[i]).philos);
	if (gettimeofday(&curr, NULL) != 0)
		ft_errors(0);
	(*data[i]).philos->number = i;
	(*data[i]).philos->last_dinner_time = curr;
	(*data[i]).semaphore = semaphore;
	(*data[i]).philos->alive = 1;
}

void	ft_init_orig_structers(t_data ***data, \
t_rules **rules, sem_t **semaphore)
{
	sem_unlink(SEMAPHORE_NAME);
	*semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, 0666, \
	(*rules)->number_of_phils / 2);
	if (*semaphore == SEM_FAILED)
	{
		printf("Semfailed %d\n", (*rules)->number_of_phils);
		exit(1);
	}
	*data = (t_data **)malloc(sizeof(t_data) * ((*rules)->number_of_phils + 1));
	ft_check_malloc(*data);
	(*data)[(*rules)->number_of_phils] = NULL;
}
