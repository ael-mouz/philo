/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:07:57 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/07/19 12:28:51 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_routine_(t_node	*philo, int x)
{
	int	time;

	time = 0;
	pthread_mutex_lock(&philo->mutex_two);
	time = get_time() - philo->_info.start;
	if (x == 1)
		philo->last_time_eat = time;
	else if (x == 2)
	{
		if (philo->_info.optional_argument)
			philo->number_of_eat++;
	}
	else if (x == 3)
		printf("%9d %3d  is eating\n", time, philo->index);
	else if (x == 4)
		printf("%9d %3d  is sleeping\n", time, philo->index);
	else if (x == 5)
		printf("%9d %3d  is thinking\n", time, philo->index);
	pthread_mutex_unlock(&philo->mutex_two);
}

void	ft_routine__(t_node *philo)
{
	int	time;

	time = 0;
	pthread_mutex_lock(&philo->mutex);
	time = get_time() - philo->_info.start;
	printf("%9d %3d  has taken a fork\n", time, philo->index);
	pthread_mutex_lock(&philo->next->mutex);
	time = get_time() - philo->_info.start;
	printf("%9d %3d  has taken a fork\n", time, philo->index);
	ft_routine_(philo, 1);
	ft_routine_(philo, 3);
	smart_usleep(philo->_info.time_to_eat);
	ft_routine_(philo, 2);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo->next->mutex);
	ft_routine_(philo, 4);
	smart_usleep(philo->_info.time_to_sleep);
	ft_routine_(philo, 5);
}

void	*ft_routine(void *arg)
{
	t_node			*philo;

	philo = (t_node *)arg;
	if (philo->index % 2 == 0)
		usleep(100);
	while (1)
		ft_routine__(philo);
	return (NULL);
}

void	create_fork_and_philo(t_info _info, t_node *philo)
{
	int		i;

	i = 0;
	while (i < _info.number_of_philosophers)
	{
		pthread_mutex_init(&philo->mutex, NULL);
		pthread_mutex_init(&philo->mutex_two, NULL);
		philo = philo->next;
		i++;
	}
	i = 0;
	while (i < _info.number_of_philosophers)
	{
		pthread_create(&philo->thread, NULL, ft_routine, philo);
		pthread_detach(philo->thread);
		philo = philo->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	_info;
	t_node	*philo;

	if (argc == 5 || argc == 6)
	{
		if (!feild_info(argc, argv, &_info))
			return (0);
		if (!ft_check_args(_info))
			return (0);
		philo = ft_creat_philosopher_list(_info);
		if (!philo)
			return (0);
		create_fork_and_philo(_info, philo);
		if (!check_philo_death(philo, _info))
			return (0);
	}
	printf("Error: Wrong number of arguments\n");
	return (0);
}
