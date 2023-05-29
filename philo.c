/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:07:57 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/05/29 21:55:26 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_node			*philo;

	philo = (t_node *)arg;
	if(philo->index % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		printf("[ %9d ] PHILO %d has taken a fork\n",get_time() - philo->_info->start ,philo->index);
		pthread_mutex_lock(&philo->next->mutex);
		printf("[ %9d ] PHILO %d has taken a fork\n",get_time() - philo->_info->start,philo->index);
		pthread_mutex_lock(&philo->mutex_two);
		philo->last_time_eat = get_time()- philo->_info->start;
		pthread_mutex_unlock(&philo->mutex_two);
		printf("[ %9d ] PHILO %d is eating\n",get_time() - philo->_info->start,philo->index);
		smart_usleep(philo->_info->time_to_eat);
		pthread_mutex_lock(&philo->mutex_tree);
		if(philo->_info->optional_argument)
			philo->number_of_eat++;
		pthread_mutex_unlock(&philo->mutex_tree);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->next->mutex);
		printf("[ %9d ] PHILO %d is sleeping\n",get_time() - philo->_info->start,philo->index);
		smart_usleep(philo->_info->time_to_sleep);
		printf("[ %9d ] PHILO %d is thinking\n",get_time() - philo->_info->start,philo->index);
	}
	return (NULL);
}

void destroy_forks(t_info *_info,t_node *philo)
{
	int i;
	
	i = 0;
	while(i < _info->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo->mutex);
		pthread_mutex_destroy(&philo->mutex_two);
		pthread_mutex_destroy(&philo->mutex_tree);
		philo = philo->next;
		i++;
	}
}

int check_philo_death(t_node *philo,t_info *_info)
{
	int time;
	int done;
	int i;
	while (1) {
		done = 0;
		i= 0;
		if(philo->_info->optional_argument)
		{
			while(i < _info->number_of_philosophers)
			{
				pthread_mutex_lock(&philo->mutex_tree);
				if(philo->number_of_eat >= _info->number_of_eat)
					done++;
				philo = philo->next;
				i++;
				pthread_mutex_unlock(&philo->mutex_tree);
			}
			if(done == _info->number_of_philosophers)
			{
				printf("[ %9d ] PHILO %d died\n",get_time() - philo->_info->start,philo->index);
				return (0);
			}
		}
		i= 0;
		time = get_time() - philo->_info->start;
		while(i < _info->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->mutex_two);
			if(time - philo->last_time_eat > philo->_info->time_to_die )
			{
				printf("[ %9d ] PHILO %d died\n",get_time() - philo->_info->start,philo->index);
				return (0);
			}
			philo = philo->next;
			i++;
			pthread_mutex_unlock(&philo->mutex_two);
		}
		// philo = philo->next;
	}
}

int	main(int argc, char **argv)
{
	t_info *_info;
	t_node *philo;
	int i ;
	

	if (argc == 5 || argc == 6)
	{
		_info = feild_info(argc, argv);
		print_info(_info);
		philo = ft_creat_philosopher_list(_info);
		i= 0;
		while(i < _info->number_of_philosophers)
		{
			pthread_mutex_init(&philo->mutex,NULL);
			pthread_mutex_init(&philo->mutex_two,NULL);
			philo = philo->next;
			i++;
		}
		i = 0;
		while(i < _info->number_of_philosophers)
		{
			pthread_create(&philo->thread, NULL, ft_routine, philo);
			pthread_detach(philo->thread);
			philo = philo->next;
			i++;
		}
		if(!check_philo_death(philo,_info))
			return 0;
	}
	else
		return (1);
}