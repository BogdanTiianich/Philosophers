/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_funcs_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:30:01 by hbecki            #+#    #+#             */
/*   Updated: 2022/05/23 14:35:23 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
void	ft_malloc_semaphores(t_semaphores **semaphores)
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

char	*init_string(char* target, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	target = (char *)malloc(sizeof(char) * (count + 1));
	ft_check_malloc(target);
	while (str[i] != '\0')
	{
		target[i] = str[i];
		i++;
	}
	target[i] = '\0';
	return (target);
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

void	ft_init_game(t_data **data, t_rules *rules, t_semaphores *semaphores, int i)
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
	(*data[i]).semaphores = semaphores;
	(*data[i]).philos->alive = 1;
}

void	ft_init_orig_structers(t_data ***data, \
t_rules **rules, t_semaphores **semaphores)
{
	char*	sem_print;
	char*	sem_forks;
	char*	sem_everyone_full;
	char*	sem_dead;
	char*	sem_start_to_eat;

	sem_print = NULL;
	sem_forks = NULL;
	sem_everyone_full = NULL;
	sem_dead = NULL;
	
	sem_forks = init_string(sem_forks, "forks\0");
	
	sem_unlink(sem_forks);
	ft_malloc_semaphores(semaphores);
	(**semaphores).forks = sem_open(sem_forks, O_CREAT, 0666, \
	(*rules)->number_of_phils / 2);
	
	if ((*semaphores)->forks == SEM_FAILED)
	{
		printf("Semfailed %d\n", (*rules)->number_of_phils);
		exit(1);
	}
	
	sem_print = init_string(sem_forks, "print\0");
	sem_unlink(sem_print);
	(*semaphores)->print = sem_open(sem_print, O_CREAT, 0666, 1);
	if ((*semaphores)->print == SEM_FAILED)
	{
		printf("Semfailed %d\n", (*rules)->number_of_phils);
		exit(1);
	}
	
	sem_everyone_full = init_string(sem_forks, "everyone_full\0");
	sem_unlink(sem_print);
	(*semaphores)->everyone_full = sem_open(sem_everyone_full, O_CREAT, 0666, -1 * (*rules)->number_of_phils);
	if ((*semaphores)->print == SEM_FAILED)
	{
		printf("Semfailed %d\n", (*rules)->number_of_phils);
		exit(1);
	}
	sem_dead = init_string(sem_dead, "print\0");
	sem_unlink(sem_dead);
	(*semaphores)->dead = sem_open(sem_dead, O_CREAT, 0666, 1);
	if ((*semaphores)->dead == SEM_FAILED)
	{
		printf("Semfailed %d\n", (*rules)->number_of_phils);
		exit(1);
	}
	*data = (t_data **)malloc(sizeof(t_data) * ((*rules)->number_of_phils + 1));
	ft_check_malloc(*data);
	(*data)[(*rules)->number_of_phils] = NULL;
	
	
}
