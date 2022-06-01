/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine_one_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:04:08 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/01 18:40:35 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_philo_eating(t_data data)
{
	t_timeval	start_eating_time;

	gettimeofday(&start_eating_time, NULL);
	data.philos->last_dinner_time = start_eating_time;
	ft_print_function(data, "is eating");
	usleep(data.rules->time_to_eat);
	return (0);
}

int	ft_philo_sleeping(t_data data)
{
	t_timeval	start_sleeping_time;

	gettimeofday(&start_sleeping_time, NULL);
	ft_print_function(data, "is sleeping");
	return (0);
}

void	ft_print_thinking(void *data)
{
	if ((*(t_data *)data).thinking_flag == 0)
	{
		ft_print_function(*(t_data *)data, "is thinking");
	}
}

int	ft_start_dinning(t_data data)
{
	int			life_and_death;

	data.thinking_flag = 0;
	sem_wait(data.semaphores->forks);
	data.thinking_flag = 1;
	ft_print_function(data, "has taken fork");
	sem_post(data.semaphores->start_eat);
	life_and_death = ft_philo_eating(data);
	sem_post(data.semaphores->forks);
	if (life_and_death == 1)
		return (1);
	return (0);
}

int	philos_life(t_data *data)
{
	int	life_and_death;
	int	quantity_of_dinners;

	quantity_of_dinners = 0;
	while (1)
	{
		life_and_death = ft_start_dinning(*data);
		quantity_of_dinners++;
		if (quantity_of_dinners >= (*data).rules->im_full_times)
			sem_post(data->semaphores->full_flag_sem[data->philos->number]);
		life_and_death = ft_philo_sleeping(*data);
		if ((*data).rules->im_full_times == -1)
			sem_post(data->semaphores->full_flag_sem[data->philos->number]);
		ft_print_function(*data, "is thinking");
	}
}
