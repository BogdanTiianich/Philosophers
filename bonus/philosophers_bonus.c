/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:51:30 by hbecki            #+#    #+#             */
/*   Updated: 2022/05/23 18:44:14 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_kill_them_all(t_data **data)
{
	sem_t	*dead;
	int		i;

	i = 0;
	dead = data[0]->semaphores->dead;
	sem_wait(dead);
	while (i < data[0]->rules->number_of_phils)
	{
		if (kill(data[i]->philos->id, SIGSEGV) == -1)
		{
			printf("KILL error %s\n", strerror(errno));
		}
		i++;
	}
}

void	kill_us(t_data data)
{
	t_timeval	start_eating_time;

	gettimeofday(&start_eating_time, NULL);
	while (1)
	{
		if (ft_time_diff_from_now_ms(start_eating_time) \
		>= data.rules->time_to_die)
		{
			ft_print_function(data, "died");
			sem_wait(data.semaphores->print);
			sem_post(data.semaphores->dead);
			exit(0);
		}
	}
}

void	update_dinner_time(t_data *data)
{
	t_timeval	start_eating_time;
	int			id;

	while (1)
	{
		id = fork();
		if (id == 0)
		{
			kill_us(*data);
		}
		sem_wait(data->semaphores->start_eat);
		kill(id, SIGSEGV);
		printf("updating last dinner time %d\n", data->philos->id);
		gettimeofday(&start_eating_time, NULL);
		data->philos->last_dinner_time = start_eating_time;
	}
}

void	ft_run_game(t_data **data, t_semaphores *semaphores, t_rules *rules)
{
	t_vars			vars;
	int				id;
	sem_t			**sem_start_eat;

	vars.i = 0;
	sem_wait(semaphores->dead);
	sem_start_eat = ft_malloc_init_semaphores(rules->number_of_phils); 
	while (vars.i < rules->number_of_phils)
	{
		ft_init_game(data, rules, semaphores, vars.i, sem_start_eat);
		id = fork();
		if (id == 0)
		{
			philos_life(data[vars.i]);
			printf("Game is over for %d\n", data[vars.i]->philos->number);
			exit(0);
		}
		else
		{
			(*data[vars.i]).philos->id = id;
			id = fork();
			if (id == 0)
				update_dinner_time(data[vars.i]);
		}	
		vars.i++;
	}
}

int	ft_waiter(int num_of_processes, t_data **data)
{
	int	i;

	i = 0;
	while (i < num_of_processes)
	{
		if (waitpid((*data[i]).philos->id, NULL, 0) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules			*rules;
	t_data			**data;
	t_semaphores	*semaphores;
	int				id;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of args\n");
		return (1);
	}
	rules = NULL;
	rules = init_rules(argc, argv);
	ft_check_malloc(rules);
	ft_init_orig_structers(&data, &rules, &semaphores);
	ft_run_game(data, semaphores, rules);
	id = fork();
	if (id == 0)
	{
		ft_kill_them_all(data);
	}
	ft_waiter(rules->number_of_phils, data);
	// sem_close(semaphore);
	exit (0);
	return (0);
}
