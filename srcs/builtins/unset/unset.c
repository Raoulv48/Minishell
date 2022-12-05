/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 16:30:14 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <libft.h>
#include <stdlib.h>
#include "unset.h"

static void	unset_initial(t_list *cur, t_list *env)
{
	char	*curc;

	while (cur != NULL)
	{
		env = g_ms->prompt->envi;
		curc = ft_strdup(cur->content);
		if (ft_strcontains(curc, "-"))
		{
			ft_dprintf(2, "unset: %s is invalid\n", curc);
			g_ms->prompt->last_exit_code = 1;
		}
		else
		{
			if (unset_initial_2(env, curc) == 0)
				;
			else
				break ;
		}
		free(curc);
		cur = cur->next;
	}
}

static void	unset_non_initial(t_list *cur, t_list *env)
{
	char	*curc;

	while (cur != NULL)
	{
		env = g_ms->prompt->envi;
		curc = ft_strdup(cur->content);
		if (ft_strcontains(curc, "-"))
		{
			ft_dprintf(2, "unset: %s is invalid\n", curc);
			g_ms->prompt->last_exit_code = 1;
		}
		else
		{
			while (env != NULL)
				env = unset_non_initial_2(env, curc);
		}
		free(curc);
		cur = cur->next;
	}
}

void	unset(void)
{
	t_list	*cur;
	t_list	*env;

	if (g_ms->prompt->argslist->next == NULL)
	{
		ft_dprintf(2, "unset: not enough arguments\n");
		g_ms->prompt->last_exit_code = 1;
	}
	cur = g_ms->prompt->argslist->next;
	env = g_ms->prompt->envi;
	unset_initial(cur, env);
	cur = g_ms->prompt->argslist->next;
	env = g_ms->prompt->envi;
	unset_non_initial(cur, env);
}
