/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 21:11:00 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stddef.h>
#include <prompt.h>

int	export_exists2(t_list *cur, char *temp, char *temp2, char *str)
{
	while (cur != NULL)
	{
		temp = getstr(str);
		temp2 = getstr(cur->content);
		if (ft_strequals(temp2, temp))
		{
			free(cur->content);
			cur->content = ft_strdup(str);
			if (temp != NULL)
			{
				free(temp);
				free (temp2);
			}
			return (1);
		}
		if (temp != NULL)
		{
			free(temp);
			free (temp2);
		}
		temp = NULL;
		temp2 = NULL;
		cur = cur->next;
	}
	return (0);
}

int	export_exists(char *str)
{
	t_list	*cur;
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	cur = g_ms->prompt->envi;
	export_exists2(cur, temp, temp2, str);
	return (export_exists2(cur, temp, temp2, str));
}

void	copy_list(void)
{
	t_list	*cur;
	t_list	*cur2;

	cur = g_ms->prompt->envi;
	g_ms->prompt->envi_copy = ft_lstnew(ft_strdup(cur->content));
	cur2 = g_ms->prompt->envi_copy;
	while (cur->next != NULL)
	{
		cur2->next = ft_lstnew(ft_strdup(cur->next->content));
		cur = cur->next;
		cur2 = cur2->next;
	}
}

static void	del(void *arg)
{
	free (arg);
}

void	restore_list(void)
{
	t_list	*cur;
	t_list	*cur2;

	cur = g_ms->prompt->envi;
	cur2 = g_ms->prompt->envi_copy;
	while (cur2 != NULL)
	{
		free(cur->content);
		cur->content = ft_strdup(cur2->content);
		cur = cur->next;
		cur2 = cur2->next;
	}
	ft_lstclear(&g_ms->prompt->envi_copy, &del);
}
