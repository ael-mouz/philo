/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:08:55 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/07/19 12:29:07 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

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
	struct s_info	_info;
	struct s_node	*next;
}					t_node;

/*--------------------PHILO_DEATH---------------------------*/
int		check_num_eat(t_node *philo, t_info _info);
int		check_death_time(t_node *philo, t_info _info);
int		check_philo_death(t_node *philo, t_info _info);
int		ft_check_args(t_info _info);

/*--------------------PHILO_HELPER----------------------------*/
int		get_time(void);
int		ft_is_whitespace(char c);
int		ft_is_digit(char *str);
void	smart_usleep(int timeto);

/*--------------------PHILO_UTILS-----------------------------*/
int		ft_atoi(char *str);
void	ft_lst_add_back(t_node **head, t_node *new);
t_node	*ft_lst_new(t_info _info, int index);
t_node	*ft_creat_philosopher_list(t_info _info);
int		feild_info(int argc, char **argv, t_info *_info);

/*--------------------PHILO-----------------------------------*/
void	ft_routine_(t_node	*philo, int x);
void	ft_routine__(t_node *philo);
void	*ft_routine(void *arg);
void	create_fork_and_philo(t_info _info, t_node *philo);

#endif