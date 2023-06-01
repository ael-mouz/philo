/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils__.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:56:05 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/06/01 22:50:45 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num_eat(t_node *philo, t_info *_info)
{
	int	i;
	int	done;

	done = 0;
	i = 0;
	if (philo->_info->optional_argument)
	{
		while (i < _info->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->mutex_two);
			if (philo->number_of_eat >= _info->number_of_eat)
				done++;
			philo = philo->next;
			i++;
			pthread_mutex_unlock(&philo->mutex_two);
			usleep(10);
		}
		if (done == _info->number_of_philosophers)
			return (0);
	}
	return (1);
}

int	check_death_time(t_node *philo, t_info *_info)
{
	int	i;
	int	time;

	i = 0;
	while (i < _info->number_of_philosophers)
	{
		pthread_mutex_lock(&philo->mutex_two);
		time = get_time() - philo->_info->start;
		if (time - philo->last_time_eat > philo->_info->time_to_die)
		{
			printf("[ %9d ] PHILO  %3d  died\n", time, philo->index);
			return (0);
		}
		philo = philo->next;
		i++;
		pthread_mutex_unlock(&philo->mutex_two);
		usleep(10);
	}
	return (1);
}

int	check_philo_death(t_node *philo, t_info *_info)
{
	while (1)
	{
		if (!check_num_eat(philo, _info))
			return (0);
		if (!check_death_time(philo, _info))
			return (0);
	}
}
