/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:07:57 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/06/05 19:25:15 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_routine_(t_node	*philo, int x)
{
	int	time;

	time = 0;
	sem_wait(philo->_info->sem_two);
	time = get_time() - philo->_info->start;
	if (x == 1)
		philo->last_time_eat = time;
	else if (x == 2)
	{
		if (philo->_info->optional_argument)
			philo->number_of_eat++;
	}
	else if (x == 3)
		printf("%9d %3d  is eating\n", time, philo->index);
	else if (x == 4)
		printf("%9d %3d  is sleeping\n", time, philo->index);
	else if (x == 5)
		printf("%9d %3d  is thinking\n", time, philo->index);
	sem_post(philo->_info->sem_two);
}

void	ft_routine__(t_node *philo)
{
	int	time;

	time = 0;
	sem_wait(philo->_info->sem);
	time = get_time() - philo->_info->start;
	printf("%9d %3d  has taken a fork\n", time, philo->index);
	sem_wait(philo->_info->sem);
	time = get_time() - philo->_info->start;
	printf("%9d %3d  has taken a fork\n", time, philo->index);
	ft_routine_(philo, 1);
	ft_routine_(philo, 3);
	smart_usleep(philo->_info->time_to_eat);
	ft_routine_(philo, 2);
	sem_post(philo->_info->sem);
	sem_post(philo->_info->sem);
	ft_routine_(philo, 4);
	smart_usleep(philo->_info->time_to_sleep);
	ft_routine_(philo, 5);
}

void	ft_checker( t_info *_info, t_node *philo)
{
	int	status;

	status = 0;
	pthread_create(&_info->thread, NULL, ft_routine_eat, philo);
	pthread_detach(_info->thread);
	waitpid(0, NULL, 0);
	kill(0, SIGINT);
}

void	create_fork_and_philo(t_info *_info, t_node *philo)
{
	int		i;

	ft_create_semaphore(_info);
	i = 0;
	while (i < _info->number_of_philosophers)
	{
		philo->pid = fork();
		if (philo->pid == 0)
		{
			pthread_create(&philo->thread, NULL, ft_routine_death, philo);
			pthread_detach(philo->thread);
			while (1)
				ft_routine__(philo);
			return ;
		}
		else if (philo->pid < 0)
		{
			perror("Error: fork failed\n");
			return ;
		}
		philo = philo->next;
		i++;
	}
	ft_checker(_info, philo);
}

int	main(int argc, char **argv)
{
	t_info	*_info;
	t_node	*philo;

	if (argc == 5 || argc == 6)
	{
		_info = feild_info(argc, argv);
		if (_info->number_of_philosophers <= 0)
			return (printf("Error: number of philo must be > 0 \n"), 0);
		if (_info->number_of_philosophers > 200)
			return (printf("Error: number of philo must be <= 200\n"), 0);
		if (_info->time_to_die < 60)
			return (printf("Error: time to die must be > 60\n"), 0);
		if (_info->time_to_eat < 60)
			return (printf("Error: time to eat must be > 60\n"), 0);
		if (_info->time_to_sleep < 60)
			return (printf("Error: time to sleep must be > 60\n"), 0);
		if (_info->optional_argument && _info->number_of_eat <= 0)
			return (printf("Error: number of eat must be > 0\n"), 0);
		philo = ft_creat_philosopher_list(_info);
		create_fork_and_philo(_info, philo);
		return (ft_destroy_forks(_info), 0);
	}
	printf("Error: Wrong number of arguments\n");
	return (0);
}
