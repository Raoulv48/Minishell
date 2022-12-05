/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   populate_list.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 14:16:23 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 14:16:24 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>

static	t_list	*set_to_list(char *dummy, t_list *newlist)
{
	if (dummy[0] == ' ' && g_ms->prompt->one_space == 1
		&& ft_str_only_contains(dummy, " ") && ft_strlen(dummy) < 2)
		return (newlist);
	else if (dummy[0] == '\0' && g_ms->prompt->one_space == 1
		&& ft_str_only_contains(dummy, "") && ft_strlen(dummy) < 1)
	{
		if (g_ms->prompt->q_bool_envar == 0)
		{
			newlist = ft_lstnew(ft_strdup(dummy));
			ft_lstadd_back(&g_ms->prompt->argslist, newlist);
			g_ms->prompt->one_space = 0;
		}
	}
	else if (dummy != NULL && dummy[0] != '\0'
		&& !ft_strequals(dummy, "")
		&& (!ft_str_only_contains(dummy, " ") || ft_strlen(dummy) > 1))
	{
		newlist = ft_lstnew(ft_strdup(dummy));
		ft_lstadd_back(&g_ms->prompt->argslist, newlist);
		g_ms->prompt->one_space = 0;
	}
	return (newlist);
}

t_list	*populate_list(t_list *newlist)
{
	char	*dummy;

	g_ms->prompt->i_list = 0;
	while (g_ms->prompt->i_list < g_ms->prompt->argv)
	{
		dummy = ft_strdup(g_ms->prompt->args[g_ms->prompt->i_list]);
		if (dummy[0] != ' ' && dummy != NULL)
		{
			dummy = join_quote(dummy);
			g_ms->prompt->one_space = 1;
		}
		if (dummy[0] == ' ' && g_ms->prompt->one_space == 1
			&& ft_str_only_contains(dummy, " ") && ft_strlen(dummy) < 2)
		{
			newlist = ft_lstnew(ft_strdup(dummy));
			ft_lstadd_back(&g_ms->prompt->argslist, newlist);
			g_ms->prompt->one_space = 0;
		}
		else
			newlist = set_to_list(dummy, newlist);
		g_ms->prompt->i_list++;
		reset_list_values(dummy);
	}
	return (newlist);
}
