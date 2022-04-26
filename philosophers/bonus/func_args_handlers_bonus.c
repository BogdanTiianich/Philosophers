/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_args_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:27:09 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/26 20:27:26 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((int)str[i] < 48 || (int)str[i] > 58)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_isnumber(argv[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int static	ft_atoi_help(const char *s, int *ngtv, int *i)
{
	int	a;

	*i = 0;
	*ngtv = 0;
	while (((s[*i] == 32) || (s[*i] == 9) || ((s[*i] >= 10) \
	&& (s[*i] <= 13))) && (s[*i] != '\0'))
		(*i)++;
	if (((s[*i] == '-') || (s[*i] == '+')) && (s[*i] != '\0'))
	{
		if (s[*i] == '-')
			(*ngtv)++;
		(*i)++;
	}
	a = *i + *ngtv - *i;
	return (a);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	result;
	int	ngtv;
	int	count;

	result = 0;
	count = 0;
	ngtv = ft_atoi_help(s, &ngtv, &i);
	while (((s[i] >= '0') && (s[i] <= '9')) && (s[i] != '\0'))
	{
		count++;
		result = result * 10 + s[i] - '0';
		i++;
	}
	if (count >= 19)
		return (-1 * (1 - ngtv));
	if (ngtv % 2 != 0)
		result *= -1;
	return (result);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	if (s == NULL || fd < 0)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
