/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_lst_content.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 23:15:04 by jlensing      #+#    #+#                 */
/*   Updated: 2020/11/03 13:08:34 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/libft.h"

void	*ft_get_lst_content(t_list *lst, unsigned int index)
{
	t_list			*cur;
	unsigned int	i;

	cur = lst;
	i = 0;
	while (cur != NULL && i < index)
	{
		cur = cur->next;
		i++;
	}
	if (cur == NULL)
		return (NULL);
	return (cur->content);
}
