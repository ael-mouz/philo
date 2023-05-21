/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:37:01 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/05/16 19:01:39 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_node	*ft_lst_new(t_info *_info, int index)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->thread = NULL;
	// new_node->mutex = NULL;
	new_node->index = index;
	new_node->time_to_die = _info->time_to_die;
	new_node->time_to_eat = _info->time_to_eat;
	new_node->time_to_sleep = _info->time_to_sleep;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lst_add_back(t_node **head, t_node *new)
{
	t_node	*copy_head;

	if (!*head)
		*head = new;
	else
	{
		copy_head = *head;
		while ((*head)->next)
		{
			*head = (*head)->next;
		}
		(*head)->next = new;
		*head = copy_head;
	}
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

t_node	*ft_creat_philosopher(t_info *_info)
{
	t_node	*philo;
	int		i;

	philo = NULL;
	i = 1;
	while (i <= _info->number_of_philosophers)
		ft_lst_add_back(&philo, ft_lst_new(_info, i++));
	ft_lst_add_back(&philo,philo);
	print_linked_list(philo,_info->number_of_philosophers);
	return(philo);
}

int	ft_list_size(t_node *list)
{
	if (!list)
		return (0);
	return (1 + ft_list_size(list->next));
}