/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:11:00 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/05/29 22:16:49 by ael-mouz         ###   ########.fr       */
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

void smart_usleep(int timeto)
{
	int time ;
	
	time = get_time();
	while(get_time() - time < timeto)
		usleep(300);
}

void	print_linked_list(t_node *head,int num)
{
	int i = 0;
	printf("---------------------------------------------\n");
	printf("| index | current_address |  next_address   |\n");
	printf("---------------------------------------------\n");
	while (i++ < num)
	{
		printf("| %5d | %15p | %15p |\n", head->index, head, head->next);
		head = head->next;
	}
	printf("---------------------------------------------\n");
}

void	print_info(t_info *_info)
{
	printf("number_of_philosophers %d \n", _info->number_of_philosophers);
	printf("time_to_die %d \n", _info->time_to_die);
	printf("time_to_eat %d \n", _info->time_to_eat);
	printf("time_to_sleep %d \n", _info->time_to_sleep);
	printf("number_of_eat %d \n", _info->number_of_eat);
	printf("optional_argument %d \n", _info->optional_argument);
	printf("*****************************************************\n");
}