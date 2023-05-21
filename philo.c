/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:07:57 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/05/16 19:55:52 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*feild_info(int argc, char **argv)
{
	t_info	*_info;

	_info = (t_info *)malloc(sizeof(t_info) * 1);
	_info->number_of_philosophers = atoi(argv[1]);
	_info->time_to_die = atoi(argv[2]);
	_info->time_to_eat = atoi(argv[3]);
	_info->time_to_sleep = atoi(argv[4]);
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
	struct timeval	tv;
	t_node			*philo;

	gettimeofday(&tv, NULL);
	philo = (t_node *)arg;
	printf("%d PHILO %d\n",tv.tv_usec ,philo->index);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info *_info;
	t_node *philo;

	if (argc == 5 || argc == 6)
	{
		_info = feild_info(argc, argv);
		print_info(_info);
		philo = ft_creat_philosopher(_info);
		pthread_create(&philo->thread, NULL, ft_routine, philo);
		pthread_create(&philo->next->thread, NULL, ft_routine, philo->next);
		pthread_create(&philo->next->next->thread, NULL, ft_routine,
				philo->next->next);
		while (1)
		{
		}
	}
	else
		return (1);
}