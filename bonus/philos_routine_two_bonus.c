/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine_two_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:04:08 by hbecki            #+#    #+#             */
/*   Updated: 2022/06/01 20:25:36 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

// int	ft_check_if_dead(t_data data)
// {
// 	if (ft_time_diff_from_now_ms(data.philos->last_dinner_time) \
// 	>= data.rules->time_to_die)
// 	{
// 		ft_print_function(data, "died");
// 		sem_wait(data.semaphores->print);
// 		sem_post(data.semaphores->dead);
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

sem_t	**ft_start_full_sem(sem_t **sems)
{
	int	i;

	i = 0;
	while (sems[i] != NULL)
	{
		sem_wait(sems[i]);
		i++;
	}
	return (sems);
}
