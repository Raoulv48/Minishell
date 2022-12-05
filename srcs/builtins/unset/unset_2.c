/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 14:15:47 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 14:15:48 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <builtins.h>
#include <stdlib.h>
#include "unset.h"

static char	*getstr(char *str)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			ret = ft_substr(str, 0, i);
			break ;
		}
		i++;
	}
	return (ret);
}

int	unset_initial_2(t_list *env, char *curc)
{
	char	*temp;

	if (env != NULL)
		temp = getstr(env->content);
	if (ft_strncmp(curc, temp, ft_strlen(curc)) == 0
		&& ft_strlen(curc) == ft_strlen(temp))
		g_ms->prompt->envi = ft_del_lst_index(g_ms->prompt->envi, 0);
	else
	{
		free(curc);
		if (temp != NULL)
			free (temp);
		temp = NULL;
		return (1);
	}
	if (temp != NULL)
		free(temp);
	temp = NULL;
	return (0);
}

t_list	*unset_non_initial_2(t_list *env, char *curc)
{
	char	*temp;

	temp = NULL;
	if (env->next != NULL)
		temp = getstr((env->next->content));
	if (env->next != NULL)
		if (ft_strncmp(curc, temp,
				ft_strlen(curc)) == 0
			&& ft_strlen(curc) == ft_strlen(temp))
			ft_del_lst_index(env, 1);
	env = env->next;
	if (temp != NULL)
		free(temp);
	temp = NULL;
	return (env);
}
