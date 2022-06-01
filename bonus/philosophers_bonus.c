/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:51:30 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/01 20:59:56 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_everyone_full_check(t_data **data)
{
	int	i;

	i = 0;
	while (i < data[0]->rules->number_of_phils)
	{
		sem_wait((*data[0]).semaphores->full_flag_sem[i]);
		i++;
	}
	sem_post(data[0]->semaphores->dead);
	sem_post(data[0]->semaphores->dead_flag_to_kill);
	sem_wait(data[0]->semaphores->print);
	exit(0);
}

void	ft_kill_them_all(t_data **data)
{
	sem_t	*dead;
	int		i;

	i = 0;
	dead = data[0]->semaphores->dead;
	sem_wait(dead);
	while (i < data[0]->rules->number_of_phils)
	{
		kill(data[i]->philos->id[0], SIGSEGV);
		kill(data[i]->philos->id[1], SIGSEGV);
		i++;
	}
	sem_post(dead);
	sem_wait(data[0]->semaphores->print);
	printf("KILLED\n");
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
			sem_post(data.semaphores->dead);
			sem_post(data.semaphores->dead_flag_to_kill);
			sem_wait(data.semaphores->print);
			exit(0);
		}
	}
	exit(0);
}

void	ft_kill_us_kill(int id, sem_t *dead)
{
	sem_wait(dead);
	kill(id, SIGSEGV);
	printf("KILLED killer\n");
	exit(0);
}

void	update_dinner_time(t_data *data)
{
	t_timeval	start_eating_time;
	int			id_kill_us;
	int			id_kill_us_kill;

	while (1)
	{
		id_kill_us = fork();
		if (id_kill_us == 0)
		{
			kill_us(*data);
			exit(0);
		}
		id_kill_us_kill = fork();
		if (id_kill_us_kill == 0)
		{
			ft_kill_us_kill(id_kill_us, data->semaphores->dead_flag_to_kill);
			exit(0);
		}
		sem_wait(data->semaphores->start_eat);
		kill(id_kill_us, SIGSEGV);
		kill(id_kill_us_kill, SIGSEGV);
		gettimeofday(&start_eating_time, NULL);
		data->philos->last_dinner_time = start_eating_time;
	}
	exit(0);
}

void	ft_run_game(t_data **data, t_semaphores *semaphores, t_rules *rules)
{
	t_vars			vars;
	int				id;
	sem_t			**sem_start_eat;
	t_rules_sems	rules_sems;

	vars.i = 0;
	sem_wait(semaphores->dead);
	sem_start_eat = ft_malloc_init_semaphores(rules->number_of_phils);
	rules_sems.rules = rules;
	rules_sems.sems = semaphores;
	while (vars.i < rules->number_of_phils)
	{
		ft_init_game(data, rules_sems, vars.i, sem_start_eat);
		id = fork();
		if (id == 0)
		{
			philos_life(data[vars.i]);
			exit(0);
		}
		else
		{
			(*data[vars.i]).philos->id[0] = id;
			id = fork();
			if (id == 0)
			{
				update_dinner_time(data[vars.i]);
				exit(0);
			}
			(*data[vars.i]).philos->id[1] = id;
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
		if (waitpid((*data[i]).philos->id[0], NULL, 0) == -1)
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
		ft_everyone_full_check(data);
		exit(0);
	}
	id = fork();
	if (id == 0)
	{
		ft_kill_them_all(data);
		exit(0);
	}
	ft_waiter(rules->number_of_phils, data);
	printf("FINISH\n");
	exit (0);
	return (0);
}
