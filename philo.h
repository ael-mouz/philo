/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:08:55 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/05/16 19:55:12 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/time.h>

typedef struct s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				optional_argument;
}					t_info;

typedef struct s_node
{
	int				index;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	struct s_node	*next;
}					t_node;

t_node	*ft_creat_philosopher(t_info *_info);
#endif