/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:23:30 by mazhari           #+#    #+#             */
/*   Updated: 2022/03/28 20:43:08 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_atoi(const char *str)
{
	int	rus;
	int	vul;
	int	i;

	i = 0;
	vul = 1;
	rus = 0;
	while ((str[i] == ' ' || str[i] == '\f')
		|| (str[i] == '\n' || str[i] == '\r')
		|| (str[i] == '\t' || str[i] == '\v'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			vul *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rus = (rus * 10) + ((int)str[i] - '0');
		i++;
	}	
	return (vul * rus);
}
