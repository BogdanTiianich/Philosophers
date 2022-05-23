/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:29:09 by hbecki            #+#    #+#             */
/*   Updated: 2022/05/13 13:58:12 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_time_diff_from_now_ms(t_timeval t1)
{
	long		diff;
	t_timeval	t2;

	gettimeofday(&t2, NULL);
	diff = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
	return (diff);
}

long	ft_time_from_start(t_timeval t)
{
	return (ft_time_diff_from_now_ms(t) / 1000);
}

void	ft_print_function(t_data data, char *message)
{

	pthread_mutex_lock(data.print_mutex);
	if (*data.dead_member != 1)
	{
		printf("%lu  %d %s\n", \
		ft_time_from_start(data.rules->start_time), data.philos->number, message);
		pthread_mutex_unlock(data.print_mutex);
	}
	else
		exit(0);
}
