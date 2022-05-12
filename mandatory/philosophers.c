/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:51:30 by hbecki            #+#    #+#             */
/*   Updated: 2022/05/12 21:10:19 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_run_game(t_data **data, pthread_t \
*threads, t_rules *rules, pthread_mutex_t **avail_forks)
{
	t_vars			vars;
	pthread_mutex_t	take_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	print_mutex;

	vars.i = 0;
	if (pthread_mutex_init(&take_mutex, NULL) != 0)
		ft_errors(0);
	if (pthread_mutex_init(&dead_mutex, NULL) != 0)
		ft_errors(0);
	if (pthread_mutex_init(&print_mutex, NULL) != 0)
		ft_errors(0);
	while (vars.i < rules->number_of_phils)
	{
		ft_init_game(data, rules, avail_forks, vars.i);
		(*data[vars.i]).take_mutex = &take_mutex;
		(*data[vars.i]).dead_mutex = &dead_mutex;
		(*data[vars.i]).print_mutex = &print_mutex;
		if (pthread_create(&threads[vars.i], NULL, &philos_life, \
		data[vars.i]) != 0)
			ft_errors(0);
		vars.i++;
	}
	vars.i = 0;
	while (vars.i < rules->number_of_phils)
	{
		pthread_join(threads[vars.i], NULL);
		vars.i++;
	}
}

int	main(int argc, char **argv)
{
	t_rules			*rules;
	pthread_t		*threads;
	t_data			**data;
	pthread_mutex_t	*avail_forks;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of args\n");
		return (1);
	}
	rules = init_rules(argc, argv);
	ft_check_malloc(rules);
	threads = (pthread_t *)malloc(sizeof(pthread_t) * \
	(rules->number_of_phils));
	ft_check_malloc(threads);
	data = (t_data **)malloc(sizeof(t_data) * (rules->number_of_phils + 1));
	ft_check_malloc(data);
	avail_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* rules->number_of_phils);
	ft_check_malloc(avail_forks);
	ft_forks_init(avail_forks, rules->number_of_phils);
	data[rules->number_of_phils] = NULL;
	ft_run_game(data, threads, rules, &avail_forks);
	exit (0);
	return (0);
}
