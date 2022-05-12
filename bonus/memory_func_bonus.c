/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_func_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:07:20 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/26 21:46:18 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_errors(int code)
{
	if (code == 1)
		printf("malloc error\n");
	if (code == 2)
		printf("args error\n");
	if (code == 0)
		ft_putstr_fd(strerror(errno), 2);
	exit(1);
}

void	ft_free(void **pointer)
{
	if (*pointer != NULL)
	{
		free(*pointer);
		*pointer = NULL;
	}
}

void	ft_check_malloc(void *data)
{
	if (data == NULL)
		ft_errors(1);
}
