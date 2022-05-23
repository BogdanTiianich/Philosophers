/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine_two_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:04:08 by hbecki            #+#    #+#             */
/*   Updated: 2022/05/17 18:05:32 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_check_if_dead(t_data data)
{
	if (ft_time_diff_from_now_ms(data.philos->last_dinner_time) \
	>= data.rules->time_to_die)
	{
		ft_print_function(data, "died");
		// sem_wait(data.semaphores->print);
		sem_post(data.semaphores->dead);
		return (1);
	}
	else
		return (0);
}
