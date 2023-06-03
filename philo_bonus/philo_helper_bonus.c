/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:11:00 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/06/03 22:03:04 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	ft_create_semaphore(t_info *_info)
{
	int	num;

	num = _info->number_of_philosophers;
	sem_unlink("/semaphore1");
	sem_unlink("/semaphore2");
	sem_unlink("/semaphore3");
	_info->sem = sem_open("/semaphore1", O_CREAT | O_EXCL, 0644, num);
	_info->sem_two = sem_open("/semaphore2", O_CREAT | O_EXCL, 0644, 1);
	_info->sem_tree = sem_open("/semaphore3", O_CREAT | O_EXCL, 0644, 0);
}

void	ft_destroy_forks(t_info *_info)
{
	sem_close(_info->sem);
	sem_close(_info->sem_two);
	sem_close(_info->sem_tree);
	sem_unlink("/semaphore1");
	sem_unlink("/semaphore2");
	sem_unlink("/semaphore3");
	return ;
}
