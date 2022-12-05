/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_del_lst_index.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 23:15:01 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 14:46:00 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/libft.h"
#include <stdlib.h>

static t_list	*del_first(t_list *lst)
{
	t_list	*cur;

	cur = lst->next;
	free(lst->content);
	free(lst);
	return (cur);
}

static t_list	*loop_list(t_list *cur, unsigned int index)
{
	unsigned int	i;

	i = 0;
	while (cur != NULL && i < index)
	{
		cur = cur->next;
		i++;
	}
	return (cur);
}

t_list	*ft_del_lst_index(t_list *lst, unsigned int index)
{
	t_list			*cur;
	t_list			*prev;
	unsigned int	i;

	if (index == 0)
		return (del_first(lst));
	cur = lst;
	cur = loop_list(cur, index);
	if (cur == NULL)
		return (NULL);
	prev = lst;
	i = 0;
	while (i < index - 1)
	{
		prev = prev->next;
		i++;
	}
	if (cur->next == NULL)
		prev->next = NULL;
	else
		prev->next = cur->next;
	free(cur->content);
	free(cur);
	return (lst);
}
