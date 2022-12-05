/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 16:30:06 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>
#include "export.h"

static char	*add_quotes(char *str)
{
	char	*sub1;
	char	*sub2;
	char	*res;
	int		i;

	if (ft_strncmp(str, "OLDPWD=", 7) == 0)
		return (ft_substr(str, 0, 6));
	i = 0;
	while (str[i] != '=')
		i++;
	sub1 = ft_substr(str, 0, i + 1);
	sub2 = ft_substr(str, i + 1, ft_strlen(str));
	res = ft_strjoin(sub1, "\"");
	res = ft_strjoin(res, sub2);
	free(sub2);
	res = ft_strjoin(res, "\"");
	return (res);
}

static void	sort_list(void)
{
	t_list	*cur;
	t_list	*prev;
	char	*temp;

	cur = g_ms->prompt->envi->next;
	prev = g_ms->prompt->envi;
	copy_list();
	while (cur != NULL)
	{
		if (ft_strncmp(prev->content, cur->content,
				ft_strlen(prev->content)) > 0)
		{
			temp = ft_strdup(prev->content);
			free(prev->content);
			prev->content = ft_strdup(cur->content);
			free(cur->content);
			cur->content = ft_strdup(temp);
			free(temp);
			cur = g_ms->prompt->envi->next;
			prev = g_ms->prompt->envi;
			continue ;
		}
		cur = cur->next;
		prev = prev->next;
	}
}

static void	no_args(t_list *cur)
{
	t_list	*env;
	char	*temp;

	if (cur == NULL)
	{
		sort_list();
		env = g_ms->prompt->envi;
		while (env != NULL)
		{
			temp = add_quotes(env->content);
			ft_printf("declare -x %s\n", temp);
			env = env->next;
			free(temp);
		}
		restore_list();
	}
}

/*
** This will export the value in the argument into the enviromental variables
** It will do this by checking for a =
** In the real bash it can always export a variable aslong as = is present
** it does not matter wether the variable is empty or not
*/

void	export_function(void)
{
	t_list	*newlist;
	t_list	*cur;
	char	*temp;
	int		ret;

	cur = g_ms->prompt->argslist->next;
	no_args(cur);
	while (cur != NULL)
	{
		temp = ft_strdup(cur->content);
		if (ft_strcontains(temp, "=")
			&& *temp != '=' && !ft_strcontains(temp, "-"))
		{
			ret = export_exists(temp);
			if (!ret && ft_strcontains(cur->content, "=") && *temp != '=')
			{
				newlist = ft_lstnew(ft_strdup(temp));
				ft_lstadd_back(&g_ms->prompt->envi, newlist);
			}
		}
		cur = cur->next;
		free(temp);
	}
}
