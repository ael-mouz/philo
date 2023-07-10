/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:56:05 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/07/10 23:24:54 by ael-mouz         ###   ########.fr       */
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
			printf("%9d %3d  died\n", time, philo->index);
			pthread_mutex_unlock(&philo->mutex_two);
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

int	ft_check_args(t_info *_info)
{
	if (_info->number_of_philosophers <= 0)
		return (printf("Error: number of philo must be > 0 \n"), 0);
	if (_info->time_to_die <= 0)
		return (printf("Error: time to die must be > 0\n"), 0);
	if (_info->time_to_eat <= 0)
		return (printf("Error: time to eat must be > 0\n"), 0);
	if (_info->time_to_sleep <= 0)
		return (printf("Error: time to sleep must be > 0\n"), 0);
	if (_info->optional_argument && _info->number_of_eat <= 0)
		return (printf("Error: number of eat must be > 0\n"), 0);
	return (1);
}
