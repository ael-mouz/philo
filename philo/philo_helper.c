/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:11:00 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/07/19 09:01:59 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	int				time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	smart_usleep(int timeto)
{
	int	time;

	time = get_time();
	while (get_time() - time < timeto)
		usleep(400);
}

int	ft_is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\f' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int	ft_is_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '\0')
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
