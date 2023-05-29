/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:08:55 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/05/29 21:49:46 by ael-mouz         ###   ########.fr       */
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
	int				number_of_eat;
	int				optional_argument;
	int				start;
}					t_info;

typedef struct s_node
{
	int				index;
	int				last_time_eat;
	int				number_of_eat;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_two;
	pthread_mutex_t	mutex_tree;
	// pthread_mutex_t	mutex_four;
	struct s_info	*_info;
	struct s_node	*next;
}					t_node;

/*--------------------PHILO_UTILS_----------------------------*/
int		get_time();
void	smart_usleep(int timeto);
void	print_linked_list(t_node *head,int num);
void	print_info(t_info *_info);

/*--------------------PHILO_UTILS-----------------------------*/
int		ft_list_size(t_node *list);
void	ft_lst_add_back(t_node **head, t_node *new);
t_node	*ft_lst_new(t_info *_info, int index);
t_node	*ft_creat_philosopher_list(t_info *_info);
t_info	*feild_info(int argc, char **argv);

/*--------------------PHILO-----------------------------------*/

#endif