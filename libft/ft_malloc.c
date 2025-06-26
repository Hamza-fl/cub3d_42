#include "../includes/cub3d.h"

void	*err(int c)
{
	(void)c;
	perror ("cub3d\n"); //----check if perror need \n and if perror allowd
	return (NULL);
}

void	free_all(t_collect **head)
{
	t_collect	*current;
	t_collect	*next;

	if (!*head || !head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	*ft_malloc(size_t size, int mode)
{
	static t_collect	*head;
	void				*data;
	t_collect			*node;

	data = NULL;
	node = NULL;
	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return (err(25));// before return call ft_malloc (0,0);
		node = malloc(sizeof(t_collect));
		if (!node)
			return (free(data), err(25));// before return call ft_malloc (0,0);
		node->data = data;
		node->next = head;
		head = node;
	}
	else if (mode == 0)
	{
		free_all(&head);
		head = NULL;
	}
	return (data);
}