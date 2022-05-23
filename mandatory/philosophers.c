/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:51:30 by hbecki            #+#    #+#             */
/*   Updated: 2022/05/17 13:43:43 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

char*	ft_calloc_str(int	length)
{
	char	*string;
	int		i;

	string = (char *)malloc(sizeof(char) * (length + 1));
	ft_check_malloc(string);
	i = 0;
	while (i <= length)
	{
		string[i] = '\0';
		i++;
	}
	return	(string);
}
// void	*tracking_death(void *thread_struct)
// {
// 	t_threads	thread_strct;
// 	int			i;

// 	i = 0;
// 	thread_strct = *(t_threads *)thread_struct;
// 	printf("trying to unlock kill mutex\n" );
// 	pthread_mutex_lock(thread_strct.dead_mutex);
// 	printf("Starting to kill processes\n" );
// 	sleep(3);
// 	printf("%d\n", thread_strct.rules.number_of_phils);
// 	while (i < thread_strct.rules.number_of_phils)
// 	{
// 		printf("%d\n", pthread_detach(thread_strct.threads[i]));
// 		printf("Process number %d has been detached\n", i);
// 		i++;
// 	}
// 	pthread_mutex_unlock(thread_strct.dead_mutex);
// 	return (NULL);
// }

void	*tracking_success(void *thread_struct)
{
	t_threads	thread_strct;
	int			i;

	i = 0;
	thread_strct = *(t_threads *)thread_struct;
	// printf("trying to unlock kill mutex\n" );
	// pthread_mutex_lock(thread_strct.dead_mutex);
	// printf("Starting to kill processes\n" );
	// sleep(3);
	// printf("%d\n", thread_strct.rules.number_of_phils);
	// while (i < thread_strct.rules.number_of_phils)
	// {
	// 	printf("%d\n", pthread_detach(thread_strct.threads[i]));
	// 	printf("Process number %d has been detached\n", i);
	// 	i++;
	// }
	while (1)
	{
		i = 0;
		while (thread_strct.finished[i] != '\0')
		{
			i++;
			if ( i == thread_strct.rules.number_of_phils)
			{
				pthread_mutex_lock(thread_strct.print_mutex);
				pthread_mutex_unlock(thread_strct.dead_mutex);
				return (NULL);
			}	
		}
	}
	// pthread_mutex_unlock(thread_strct.dead_mutex);
	return (NULL);
}

int	tracking_death(t_threads *thread_struct)
{
	t_threads	thread_strct;
	int			i;

	i = 0;
	thread_strct = *thread_struct;
	pthread_mutex_lock(thread_strct.dead_mutex);
	while (i < thread_strct.rules.number_of_phils)
	{
		pthread_detach(thread_strct.threads[i]);
		i++;
	}
	pthread_mutex_unlock(thread_strct.dead_mutex);
	return (0);
}

void	ft_run_game(t_data **data, t_threads \
threads_struct, t_rules *rules, pthread_mutex_t **avail_forks)
{
	t_vars			vars;
	pthread_mutex_t	take_mutex;
	int				dead_member;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	char			*finished;

	vars.i = 0;
	dead_member = 0;
	if (pthread_mutex_init(&take_mutex, NULL) != 0)
		ft_errors(0);
	if (pthread_mutex_init(&dead_mutex, NULL) != 0)
		ft_errors(0);
	if (pthread_mutex_init(&print_mutex, NULL) != 0)
		ft_errors(0);
	pthread_mutex_lock(&dead_mutex);
	threads_struct.rules = *rules;
	threads_struct.dead_mutex = &dead_mutex;
	finished = ft_calloc_str(rules->number_of_phils);
	threads_struct.finished = finished;
	threads_struct.print_mutex = &print_mutex;
	while (vars.i < rules->number_of_phils)
	{
		ft_init_game(data, rules, avail_forks, vars.i);
		(*data[vars.i]).take_mutex = &take_mutex;
		(*data[vars.i]).dead_mutex = &dead_mutex;
		(*data[vars.i]).dead_member = &dead_member;
		(*data[vars.i]).print_mutex = &print_mutex;
		(*data[vars.i]).finished = finished;
		if (vars.i % 2 == 1)
		{
			if (pthread_create(&threads_struct.threads[vars.i], NULL, &philos_life, \
				data[vars.i]) != 0)
			ft_errors(0);
		}
		vars.i++;
	}
	vars.i = 0;
	while (vars.i < rules->number_of_phils)
	{
		ft_init_game(data, rules, avail_forks, vars.i);
		(*data[vars.i]).take_mutex = &take_mutex;
		(*data[vars.i]).dead_mutex = &dead_mutex;
		(*data[vars.i]).dead_member = &dead_member;
		(*data[vars.i]).print_mutex = &print_mutex;
		(*data[vars.i]).finished = finished;
		if (vars.i % 2 == 0)
		{
			if (pthread_create(&threads_struct.threads[vars.i], \
			NULL, &philos_life, data[vars.i]) != 0)
			ft_errors(0);
		}
		vars.i++;
	}
	if (pthread_create(&threads_struct.threads[rules->number_of_phils], \
			NULL, &tracking_success, &threads_struct) != 0)
		ft_errors(0);
	tracking_death(&threads_struct);
	vars.i = 0;
	
	while (vars.i < rules->number_of_phils)
	{
		pthread_join(threads_struct.threads[vars.i], NULL);
		vars.i++;
	}
	// pthread_join(threads_struct.threads[rules->number_of_phils], NULL);
}

int	main(int argc, char **argv)
{
	t_rules			*rules;
	t_threads		threads_struct;
	t_data			**data;
	pthread_mutex_t	*avail_forks;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of args\n");
		return (1);
	}
	rules = init_rules(argc, argv);
	ft_check_malloc(rules);
	threads_struct.threads = (pthread_t *)malloc(sizeof(pthread_t) * \
	(rules->number_of_phils + 1));
	ft_check_malloc(threads_struct.threads);
	data = (t_data **)malloc(sizeof(t_data) * (rules->number_of_phils + 1));
	ft_check_malloc(data);
	avail_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* rules->number_of_phils);
	ft_check_malloc(avail_forks);
	ft_forks_init(avail_forks, rules->number_of_phils);
	data[rules->number_of_phils] = NULL;
	ft_run_game(data, threads_struct, rules, &avail_forks);
	exit (0);
	return (0);
}
