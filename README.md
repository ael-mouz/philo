# philo


### to test the data of _info and philo linked list

```c
void	print_linked_list(t_node *head, int num)
{
	int	i;

	i = 0;
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
```

```c
void	print_info(t_info *_info)
{
	printf("number_of_philosophers %d \n", _info->number_of_philosophers);
	printf("time_to_die %d \n", _info->time_to_die);
	printf("time_to_eat %d \n", _info->time_to_eat);
	printf("time_to_sleep %d \n", _info->time_to_sleep);
	printf("number_of_eat %d \n", _info->number_of_eat);
	printf("optional_argument %d \n", _info->optional_argument);
}
```