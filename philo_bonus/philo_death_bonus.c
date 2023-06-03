/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:56:05 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/06/03 22:02:57 by ael-mouz         ###   ########.fr       */
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
		sem_post(philo->_info->sem_two);
		printf("[ %9d ] PHILO  %3d  died\n", time, philo->index);
		exit(0);
	}
	sem_post(philo->_info->sem_two);
	usleep(10);
	return (1);
}

int	check_philo_death(t_node *philo, t_info *_info)
{
	while (1)
	{
		if (!check_num_eat(philo, _info))
			return (0);
		if (!check_death_time(philo))
			return (0);
	}
}

void	*ft_routine_death(void *arg)
{
	t_node	*philo;

	philo = (t_node *)arg;
	check_philo_death(philo, philo->_info);
	return (NULL);
}

void	*ft_routine_eat(void *arg)
{
	t_node	*philo;
	int		done;

	done = 0;
	philo = (t_node *)arg;
	while (1)
	{
		if (done >= philo->_info->number_of_philosophers)
		{
			sem_post(philo->_info->sem_tree);
			kill(philo->pid, SIGINT);
		}
		sem_wait(philo->_info->sem_tree);
		done++;
	}
	return (NULL);
}
