/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 16:29:04 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <prompt.h>
#include <stdlib.h>

/*
** Get all the variables stored in the g_ms->prompt->envi linked list
** and print these out. Simple as that
*/

static char	*remove_spaces(char *str)
{
	char	*res;
	int		i;

	i = ft_strlen(str);
	while (str[i] == ' ')
		i--;
	res = ft_substr(str, 0, i - 1);
	return (res);
}

void	env(void)
{
	t_list	*cur;
	char	*temp;

	temp = NULL;
	if (g_ms->prompt->argslist->next != NULL)
		temp = remove_spaces(g_ms->prompt->argslist->next->content);
	if (temp != NULL)
	{
		if (!ft_strequals(temp, ">") && !ft_strequals(temp, ">>"))
		{
			ft_dprintf(2, "env: Too many arguments (expected none)\n");
			free(temp);
			return ;
		}
		free(temp);
	}
	cur = g_ms->prompt->envi;
	while (cur != NULL)
	{
		ft_printf("%s\n", cur->content);
		cur = cur->next;
	}
}
