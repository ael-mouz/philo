/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:07:57 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/05/23 20:59:32 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_time()
{
	struct timeval	tv;
	int time;
	
	gettimeofday(&tv, NULL);
	time = tv.tv_sec *1000 + tv.tv_usec/1000;
	return (time);
}
t_info	*feild_info(int argc, char **argv)
{
	t_info	*_info;

	_info = (t_info *)malloc(sizeof(t_info) * 1);
	_info->number_of_philosophers = atoi(argv[1]);
	_info->time_to_die = atoi(argv[2]);
	_info->time_to_eat = atoi(argv[3]);
	_info->time_to_sleep = atoi(argv[4]);
	_info->start = get_time();
	if (argc == 6)
	{
		_info->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
		_info->optional_argument = 0;
	}
	else
	{
		_info->number_of_times_each_philosopher_must_eat = 0;
		_info->optional_argument = 0;
	}
	return (_info);
}
void	print_info(t_info *_info)
{
	printf("number_of_philosophers %d \n", _info->number_of_philosophers);
	printf("time_to_die %d \n", _info->time_to_die);
	printf("time_to_eat %d \n", _info->time_to_eat);
	printf("time_to_sleep %d \n", _info->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat %d \n",
			_info->number_of_times_each_philosopher_must_eat);
}

void	*ft_routine(void *arg)
{
	
	t_node			*philo;

	
	philo = (t_node *)arg;
	if(philo->index % 2 == 0)
		usleep(100000);
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		printf("%d PHILO %d has taken a fork\n",get_time() - philo->_info->start ,philo->index);
		pthread_mutex_lock(&philo->next->mutex);
		printf("%d PHILO %d has taken a fork\n",get_time() - philo->_info->start,philo->index);
		philo->last_time_eat = get_time()- philo->_info->start;
		printf("%d PHILO %d is eating\n",get_time() - philo->_info->start,philo->index);
		usleep(philo->_info->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->next->mutex);
		printf("%d PHILO %d is sleeping\n",get_time() - philo->_info->start,philo->index);
		usleep(philo->_info->time_to_sleep * 1000);
		printf("%d PHILO %d is thinking\n",get_time() - philo->_info->start,philo->index);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info *_info;
	t_node *philo;
	int i = 0;

	if (argc == 5 || argc == 6)
	{
		_info = feild_info(argc, argv);
		print_info(_info);
		philo = ft_creat_philosopher(_info);
		while(i < _info->number_of_philosophers)
		{
			pthread_mutex_init(&philo->mutex,NULL);
			philo = philo->next;
			i++;
		}
		i = 0;
		while(i < _info->number_of_philosophers)
		{
			pthread_create(&philo->thread, NULL, ft_routine, philo);
			philo = philo->next;
			i++;
		}
		while (1) {
			if(get_time() - philo->_info->start - philo->last_time_eat > philo->_info->time_to_die)
			{
				printf("%d PHILO %d died\n",get_time() - philo->_info->start,philo->index);
				return (0);
			}
			philo = philo->next;
		}
		i = 0;
		while(i < _info->number_of_philosophers)
		{
			pthread_join(philo->thread,NULL);
			philo = philo->next;
			i++;
		}
		i = 0;
		while(i < _info->number_of_philosophers)
		{
			pthread_mutex_destroy(&philo->mutex);
			philo = philo->next;
			i++;
		}
	}
	else
		return (1);
}