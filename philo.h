/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:08:55 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/05/23 20:53:18 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				optional_argument;
	int				start;
}					t_info;

typedef struct s_node
{
	int				index;
	int				last_time_eat;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	struct s_info	*_info;
	struct s_node	*next;
}					t_node;

t_node	*ft_creat_philosopher(t_info *_info);
int get_time();
#endif