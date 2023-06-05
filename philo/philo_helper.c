/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:11:00 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/06/05 20:28:31 by ael-mouz         ###   ########.fr       */
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

void	ft_destroy_forks(t_info *_info, t_node *philo)
{
	int	i;

	i = 0;
	while (i < _info->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo->mutex);
		pthread_mutex_destroy(&philo->mutex_two);
		philo = philo->next;
		i++;
	}
}

int	ft_is_digit(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
