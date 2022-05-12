/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:51:30 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/28 19:39:33 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_run_game(t_data **data, sem_t *semaphore, t_rules *rules)
{
	t_vars			vars;
	int				id;

	vars.i = 0;
	while (vars.i < rules->number_of_phils)
	{
		ft_init_game(data, rules, semaphore, vars.i);
		id = fork();
		if (id == 0)
		{
			philos_life(data[vars.i]);
			exit(0);
		}
		else
			(*data[vars.i]).philos->id = id;
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
	t_rules		*rules;
	t_data		**data;
	sem_t		*semaphore;

	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of args\n");
		return (1);
	}
	rules = NULL;
	rules = init_rules(argc, argv);
	ft_check_malloc(rules);
	ft_init_orig_structers(&data, &rules, &semaphore);
	ft_run_game(data, semaphore, rules);
	ft_waiter(rules->number_of_phils, data);
	sem_close(semaphore);
	exit (0);
	return (0);
}
