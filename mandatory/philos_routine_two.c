/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bogdantiyanich <bogdantiyanich@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:04:08 by hbecki            #+#    #+#             */
/*   Updated: 2022/05/16 17:01:47 by bogdantiyan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philos_life(void *data)
{
	int	life_and_death;
	int	quantity_of_dinners;

	quantity_of_dinners = 0;
	while (1)
	{
		life_and_death = ft_start_dinning(*(t_data *)data);
		if (life_and_death == 1)
			return (NULL);
		quantity_of_dinners++;
		if (quantity_of_dinners >= (*(t_data *)data).rules->im_full_times)
			(*(t_data *)data).finished[(*(t_data *)data).philos->number] = '1';
		life_and_death = ft_philo_sleeping(*(t_data *)data);
		if (life_and_death == 1)
			return (NULL);
		if ((*(t_data *)data).rules->im_full_times == -1)
			break ;
	}
	return (NULL);
}

void	ft_define_forks_i_need(t_philos *philos, int number_of_philos)
{
	if (philos->number == 0)
		philos->forks_i_need[0] = number_of_philos - 1;
	else
		philos->forks_i_need[0] = philos->number - 1;
	philos->forks_i_need[1] = philos->number;
}
