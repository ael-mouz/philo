/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:56:05 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/07/10 23:23:35 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_num_eat(t_node *philo, t_info *_info)
{
	if (philo->_info->optional_argument)
	{
		sem_wait(philo->_info->sem_two);
		if (philo->number_of_eat >= _info->number_of_eat)
		{
			sem_post(philo->_info->sem_two);
			sem_post(philo->_info->sem_tree);
			return (0);
		}
		sem_post(philo->_info->sem_two);
		usleep(10);
	}
	return (1);
}

int	check_death_time(t_node *philo)
{
	int	time;

	sem_wait(philo->_info->sem_two);
	time = get_time() - philo->_info->start;
	if (time - philo->last_time_eat > philo->_info->time_to_die)
	{
		printf("%9d %3d  died\n", time, philo->index);
		exit(0);
	}
	sem_post(philo->_info->sem_two);
	usleep(10);
	return (1);
}

void	*ft_routine_death(void *arg)
{
	t_node	*philo;

	philo = (t_node *)arg;
	while (1)
	{
		if (!check_num_eat(philo, philo->_info))
			return (NULL);
		if (!check_death_time(philo))
			return (NULL);
	}
	return (NULL);
}

void	*ft_routine_eat(void *arg)
{
	t_node	*philo;
	int		done;

	done = 0;
	philo = (t_node *)arg;
	if (philo->_info->optional_argument)
	{
		while (1)
		{
			if (done >= philo->_info->number_of_philosophers)
			{
				sem_post(philo->_info->sem_tree);
				kill(0, SIGINT);
			}
			sem_wait(philo->_info->sem_tree);
			done++;
		}
	}
	return (NULL);
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
