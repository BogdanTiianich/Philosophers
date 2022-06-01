/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:30:01 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/01 20:45:08 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

char	*init_string(char *str, char variance)
{
	int		i;
	char	*target;
	int		count;

	i = 0;
	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	target = (char *)malloc(sizeof(char) * (count + 2));
	ft_check_malloc(target);
	while (str[i] != '\0')
	{
		target[i] = str[i];
		i++;
	}
	target[i] = variance;
	target[i + 1] = '\0';
	return (target);
}

void	ft_malloc_semaphores_named(t_semaphores **semaphores)
{
	*semaphores = (t_semaphores *)malloc(sizeof(t_semaphores));
	ft_check_malloc(*semaphores);
	(*semaphores)->forks = (sem_t *)malloc(sizeof(sem_t));
	ft_check_malloc((*semaphores)->forks);
	(*semaphores)->print = (sem_t *)malloc(sizeof(sem_t));
	ft_check_malloc((*semaphores)->print);
	(*semaphores)->everyone_full = (sem_t *)malloc(sizeof(sem_t));
	ft_check_malloc((*semaphores)->everyone_full);
}

sem_t	**ft_malloc_init_semaphores(int qnt)
{
	sem_t	**sems;
	int		i;
	char	*str_tmp;

	sems = NULL;
	sems = (sem_t **)malloc(sizeof(t_semaphores *) * (qnt + 1));
	ft_check_malloc(sems);
	sems[qnt] = NULL;
	i = 0;
	while (i < qnt)
	{
		str_tmp = init_string("sem\0", (char)(i + 48));
		sem_unlink(str_tmp);
		sems[i] = sem_open(str_tmp, O_CREAT, 0666, 1);
		if (sems[i] == SEM_FAILED)
		{
			printf("Semfailed\n");
			exit(1);
		}
		free(str_tmp);
		i++;
	}
	return (sems);
}

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

void	ft_init_game(t_data **data, t_rules_sems rules_sems, \
int i, sem_t **sem_start_eat)
{
	t_timeval	curr;

	data[i] = (t_data *)malloc(sizeof(t_data));
	ft_check_malloc(data[i]);
	(*data[i]).rules = rules_sems.rules;
	(*data[i]).philos = (t_philos *)malloc(sizeof(t_philos));
	ft_check_malloc((*data[i]).philos);
	if (gettimeofday(&curr, NULL) != 0)
		ft_errors(0);
	(*data[i]).philos->number = i;
	(*data[i]).philos->last_dinner_time = curr;
	(*data[i]).semaphores = rules_sems.sems;
	(*data[i]).philos->alive = 1;
	(*data[i]).semaphores->start_eat = sem_start_eat[i];
}

void	ft_init_named_sems(sem_t **semaphore, char* str_name, int qnt)
{
	sem_unlink(str_name);
	(*semaphore) = sem_open(str_name, O_CREAT, 0666, \
	qnt);
	if ((*semaphore) == SEM_FAILED)
	{
		printf("Sem failed\n");
		exit(1);
	}
}

void	ft_init_orig_structers(t_data ***data, \
t_rules **rules, t_semaphores **semaphores)
{
	ft_malloc_semaphores_named(semaphores);
	// ft_init_named_sems(&(*semaphores)->forks, "forks\0", (*rules)->number_of_phils / 2);
	sem_unlink("forks\0");
	(*semaphores)->forks = sem_open("forks\0", O_CREAT, 0666, (*rules)->number_of_phils / 2);
	if ((*semaphores)->forks == SEM_FAILED)
	{
		printf("Semfailed %d\n", (*rules)->number_of_phils);
		exit(1);
	}
	sem_unlink("print\0");
	(*semaphores)->print = sem_open("print\0", O_CREAT, 0666, 1);
	if ((*semaphores)->print == SEM_FAILED)
	{
		printf("Semfailed %d\n", (*rules)->number_of_phils);
		exit(1);
	}
	sem_unlink("everyone_full\0");
	(*semaphores)->everyone_full = sem_open("everyone_full\0", O_CREAT, 0666, (*rules)->number_of_phils);
	if ((*semaphores)->everyone_full == SEM_FAILED)
	{
		printf("Semfailed %d\n", (*rules)->number_of_phils);
		exit(1);
	}
	sem_unlink("dead_falg_to_kill\0");
	(*semaphores)->dead_flag_to_kill = sem_open("dead_falg_to_kill\0", O_CREAT, 0666, 1);
	if ((*semaphores)->dead_flag_to_kill == SEM_FAILED)
	{
		printf("Semfailed %d\n", (*rules)->number_of_phils);
		exit(1);
	}
	sem_wait((*semaphores)->dead_flag_to_kill);
	sem_unlink("dead\0");
	(*semaphores)->dead = sem_open("dead\0", O_CREAT, 0666, 1);
	if ((*semaphores)->dead == SEM_FAILED)
	{
		printf("Semfailed %d\n", (*rules)->number_of_phils);
		exit(1);
	}
	*data = (t_data **)malloc(sizeof(t_data) * ((*rules)->number_of_phils + 1));
	ft_check_malloc(*data);
	(*semaphores)->full_flag_sem = ft_malloc_init_semaphores((*rules)->number_of_phils);
	(*semaphores)->full_flag_sem = ft_start_full_sem((*semaphores)->full_flag_sem);
	(*data)[(*rules)->number_of_phils] = NULL;
}
