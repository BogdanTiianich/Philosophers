/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:04:08 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/26 21:06:35 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
