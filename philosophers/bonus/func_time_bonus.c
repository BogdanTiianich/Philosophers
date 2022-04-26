/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:29:09 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/26 20:29:20 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
