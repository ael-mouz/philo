/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:08:55 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/06/03 22:02:18 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				optional_argument;
	int				start;
	sem_t			*sem;
	sem_t			*sem_two;
	sem_t			*sem_tree;
	pthread_t		thread;
}					t_info;

typedef struct s_node
{
	int				index;
	int				last_time_eat;
	int				number_of_eat;
	pid_t			pid;
	pthread_t		thread;
	struct s_info	*_info;
	struct s_node	*next;
}					t_node;

/*--------------------PHILO_UTILS__---------------------------*/
int		check_num_eat(t_node *philo, t_info *_info);
int		check_death_time(t_node *philo);
int		check_philo_death(t_node *philo, t_info *_info);
void	*ft_routine_death(void *arg);
void	*ft_routine_eat(void *arg);

/*--------------------PHILO_UTILS_----------------------------*/
int		get_time(void);
void	smart_usleep(int timeto);
void	ft_create_semaphore(t_info *_info);
void	ft_destroy_forks(t_info *_info);

/*--------------------PHILO_UTILS-----------------------------*/
int		ft_atoi(char *str);
void	ft_lst_add_back(t_node **head, t_node *new);
t_node	*ft_lst_new(t_info *_info, int index);
t_node	*ft_creat_philosopher_list(t_info *_info);
t_info	*feild_info(int argc, char **argv);

/*--------------------PHILO-----------------------------------*/

#endif