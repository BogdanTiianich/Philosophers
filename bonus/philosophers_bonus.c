/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:51:30 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/03 14:11:42 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_run_new_proc(void (*func)(t_data **), t_data **data, int i)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		printf("Process number %d  %d has started\n", getpid(), i);
		func(data);
		printf("Process number %d  %d is about to finish\n", getpid(), i);
		exit(0);
	}
	return (id);
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
			printf("Process number %d has started\n", getpid());
			philos_life(data[vars.i]);
			printf("Process number %d is about to finish\n", getpid());
			exit(0);
		}
		else
		{
			(*data[vars.i]).philos->id[0] = id;
			(*data[vars.i]).philos->id[1] = \
			ft_run_new_proc(update_dinner_time, &data[vars.i], 1);
			// id = fork();
			// if (id == 0)
			// {
			// 	update_dinner_time(data[vars.i]);
			// 	exit(0);
			// }
			// (*data[vars.i]).philos->id[1] = id;
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
	t_vars			vars;

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
	vars.everyone_full_id = ft_run_new_proc(ft_everyone_full_check, data, 2);
	vars.kill_them_all_id = ft_run_new_proc(ft_kill_them_all, data, 3);
	ft_waiter(rules->number_of_phils, data);
	kill(vars.everyone_full_id, SIGSEGV);
	kill(vars.kill_them_all_id, SIGSEGV);
	printf("SEM IS ON IN parent\n");
	printf("FINISH\n");
	exit (0);
	return (0);
}
