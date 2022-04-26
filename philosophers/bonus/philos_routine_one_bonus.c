/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:04:08 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/26 21:05:24 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_philo_eating(t_data data)
{
	t_timeval	start_eating_time;
	t_timeval	finished_eating_time;

	gettimeofday(&start_eating_time, NULL);
	printf("%lu  %d is eating\n", \
	ft_time_from_start(data.rules->start_time), data.philos->number);
	while (ft_time_diff_from_now_ms(start_eating_time) < \
	data.rules->time_to_eat)
	{
		if (ft_check_if_dead(data) == 1)
			return (1);
	}
	gettimeofday(&finished_eating_time, NULL);
	data.philos->last_dinner_time = finished_eating_time;
	return (0);
}

int	ft_philo_sleeping(t_data data)
{
	t_timeval	start_sleeping_time;

	gettimeofday(&start_sleeping_time, NULL);
	printf("%lu  %d is sleeping\n", \
	ft_time_from_start(data.rules->start_time), data.philos->number);
	while (ft_time_diff_from_now_ms(start_sleeping_time) < \
	data.rules->time_to_sleep)
	{	
		if (ft_check_if_dead(data) == 1)
			return (1);
	}
	return (0);
}

void	ft_print_thinking(void *data)
{
	if ((*(t_data *)data).thinking_flag == 0)
	{
		printf("%lu  %d is thinking\n", ft_time_from_start((*(t_data *)data).\
		rules->start_time), (*(t_data *)data).philos->number);
	}
}

int	ft_start_dinning(t_data data)
{
	int			life_and_death;

	data.thinking_flag = 0;
	printf("%lu  %d is thinking\n", ft_time_from_start((data).rules-> \
	start_time), (data).philos->number);
	sem_wait(data.semaphore);
	data.thinking_flag = 1;
	printf("%lu  %d has taken fork\n", \
	ft_time_from_start(data.rules->start_time), data.philos->number);
	life_and_death = ft_philo_eating(data);
	sem_post(data.semaphore);
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
		if (life_and_death == 1)
			return (0);
		quantity_of_dinners++;
		if (quantity_of_dinners >= (*data).rules->im_full_times)
			return (0);
		life_and_death = ft_philo_sleeping(*data);
		if (life_and_death == 1)
			return (0);
		if ((*data).rules->im_full_times == -1)
			return (0);
	}
}
