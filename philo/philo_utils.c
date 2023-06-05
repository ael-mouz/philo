/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mouz <ael-mouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:37:01 by ael-mouz          #+#    #+#             */
/*   Updated: 2023/06/05 20:28:45 by ael-mouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_node	*ft_lst_new(t_info *_info, int index)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->index = index;
	new_node->last_time_eat = 0;
	new_node->number_of_eat = 0;
	new_node->_info = _info;
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

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] && (str[i] == '\n' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\f' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	return (result * sign);
}

t_node	*ft_creat_philosopher_list(t_info *_info)
{
	t_node	*philo;
	int		i;

	philo = NULL;
	i = 1;
	while (i <= _info->number_of_philosophers)
		ft_lst_add_back(&philo, ft_lst_new(_info, i++));
	ft_lst_add_back(&philo, philo);
	return (philo);
}

t_info	*feild_info(int argc, char **argv)
{
	t_info	*_info;

	if (!ft_is_digit(argv[1]) || !ft_is_digit(argv[2]) || !ft_is_digit(argv[3])
		|| !ft_is_digit(argv[4]) || (argc == 6 && !ft_is_digit(argv[5])))
	{
		printf("Error: arguments must be numbers\n");
		exit(1);
	}
	_info = (t_info *)malloc(sizeof(t_info) * 1);
	_info->number_of_philosophers = ft_atoi(argv[1]);
	_info->time_to_die = ft_atoi(argv[2]);
	_info->time_to_eat = ft_atoi(argv[3]);
	_info->time_to_sleep = ft_atoi(argv[4]);
	_info->start = get_time();
	if (argc == 6)
	{
		_info->number_of_eat = ft_atoi(argv[5]);
		_info->optional_argument = 1;
	}
	else
	{
		_info->number_of_eat = 0;
		_info->optional_argument = 0;
	}
	return (_info);
}
