/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:54:48 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/03 14:13:41 by hbecki           ###   ########.fr       */
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
	printf("FULL\n");
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
	usleep(2000000);
	while (i < data[0]->rules->number_of_phils)
	{
		// kill(data[i]->philos->id[0], SIGSEGV);
		if (kill(data[i]->philos->id[0], SIGSEGV) != -1)
			printf("Process number %d is killed\n", data[i]->philos->id[0]);
		if (kill(data[i]->philos->id[1], SIGSEGV) != -1)
			printf("Process number %d is killed\n", data[i]->philos->id[1]);
		// kill(data[i]->philos->id[1], SIGSEGV);
		i++;
	}
	sem_post(dead);
	// sem_wait(data[0]->semaphores->print);
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
			sem_post(data.semaphores->dead);
			sem_post(data.semaphores->dead_flag_to_kill);
			printf("Process number %d is ready_to_die\n", getpid());
			ft_print_function(data, "died");
			sem_wait(data.semaphores->print);
			exit(0);
		}
	}
	exit(0);
}

void	ft_kill_us_kill(int id, sem_t *dead)
{
	sem_wait(dead);
	printf("Process number %d is starting to kill proce s %d\n", getpid(), id);
	if (kill(id, SIGSEGV) != -1)
		printf("Process number %d is killed kill_us_kill\n", id);
	printf("KILLED killer\n");
	exit(0);
}

void	update_dinner_time(t_data **data_exter)
{
	t_timeval	start_eating_time;
	int			id_kill_us;
	int			id_kill_us_kill;
	t_data		*data;

	data = *data_exter;
	while (1)
	{
		id_kill_us = fork();
		if (id_kill_us == 0)
		{
			printf("Process number %d has started kill_us\n", getpid());
			kill_us(*data);
			printf("Process number %d is about to finish kill_us\n", getpid());
			exit(0);
		}
		id_kill_us_kill = fork();
		if (id_kill_us_kill == 0)
		{
			printf("Process number %d has started ft_kill_us_kill\n", getpid());
			ft_kill_us_kill(id_kill_us, data->semaphores->dead_flag_to_kill);
			printf("Process number %d is about to finish ft_kill_us_kill\n", getpid());
			exit(0);
		}
		sem_wait(data->semaphores->start_eat);
		if (kill(id_kill_us, SIGSEGV) != -1)
			printf("Process number %d is killed by parent\n", id_kill_us);
		// kill(id_kill_us, SIGSEGV);
		if (kill(id_kill_us_kill, SIGSEGV) != -1)
			printf("Process number %d is killed by parent\n", id_kill_us_kill);
		// kill(id_kill_us_kill, SIGSEGV);
		gettimeofday(&start_eating_time, NULL);
		data->philos->last_dinner_time = start_eating_time;
	}
	exit(0);
}
