/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:04:08 by hbecki            #+#    #+#             */
/*   Updated: 2022/05/12 21:30:22 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_if_dead(t_data data)
{
	if (ft_time_diff_from_now_ms(data.philos->last_dinner_time) \
	>= data.rules->time_to_die)
	{
		printf("%lu  %d died\n", \
	ft_time_from_start(data.rules->start_time), data.philos->number);
		return (1);
	}
	else
		return (0);
}

int	waiting_for_forks(t_data data)
{
	int	flag;

	flag = 0;
	if (ft_check_if_dead(data) == 1)
		return (1);
	pthread_mutex_lock(data.take_mutex);
	// while (1)
	// {
		
		
		// if ((*data.avail_forks)[data.philos->forks_i_need[0]] == 1 && \
		// (*data.avail_forks)[data.philos->forks_i_need[1]] == 1)
		// {
		// 	pthread_mutex_lock(data.take_mutex);
		// 	if ((*data.avail_forks)[data.philos->forks_i_need[0]] == 1 && \
		// 	(*data.avail_forks)[data.philos->forks_i_need[1]] == 1)
		// 		break ;
		// 	else
		// 		pthread_mutex_unlock(data.take_mutex);
		// }
		// if (flag == 0)
		// {
		// 	printf("%lu  %d is thinking\n", ft_time_from_start(\
		// 	data.rules->start_time), data.philos->number);
		// 	flag = 1;
		// }
	// }
	return (0);
}

int	ft_philo_eating(t_data data)
{
	t_timeval	start_eating_time;
	t_timeval	finished_eating_time;

	pthread_mutex_unlock(data.take_mutex);
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

int	ft_start_dinning(t_data data)
{
	int	life_and_death;

	// if (waiting_for_forks(data) == 1)
		// return (1);
	if (ft_check_if_dead(data) == 1)
		return (1);
	pthread_mutex_lock(data.take_mutex);
	pthread_mutex_lock(&(*data.avail_forks)[data.philos->forks_i_need[0]]);
	pthread_mutex_lock(&(*data.avail_forks)[data.philos->forks_i_need[1]]);
	pthread_mutex_unlock(data.take_mutex);
	printf("%lu  %d has taken fork\n", \
	ft_time_from_start(data.rules->start_time), data.philos->number);
	
	
	life_and_death = ft_philo_eating(data);
	pthread_mutex_unlock(&(*data.avail_forks)[data.philos->forks_i_need[0]]);
	pthread_mutex_unlock(&(*data.avail_forks)[data.philos->forks_i_need[1]]);
	if (life_and_death == 1)
		return (1);
	return (0);
}
