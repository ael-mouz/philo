/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper__bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:18:54 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/07/10 22:19:44 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (0);
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		i++;
	while (str[i] && !ft_is_whitespace(str[i]))
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] && !ft_is_whitespace(str[i]))
		return (0);
	return (1);
}
