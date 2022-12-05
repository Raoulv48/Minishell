/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   populate_list2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 14:16:28 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 14:16:28 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>

char	*join_quote(char *dummy)
{
	if ((g_ms->prompt->i_list < g_ms->prompt->argv - 1 ) && (to_join(dummy)
			== 1 && g_ms->prompt->args[g_ms->prompt->i_list + 1] != NULL))
	{
		g_ms->prompt->i_list++;
		while ((g_ms->prompt->i_list < g_ms->prompt->argv - 1)
			&& (to_join(dummy) == 1
				&& g_ms->prompt->args[g_ms->prompt->i_list + 1] != NULL))
		{
			dummy = ft_strjoin(dummy, g_ms->prompt->args[g_ms->prompt->i_list]);
			g_ms->prompt->i_list++;
		}
		dummy = ft_strjoin(dummy, g_ms->prompt->args[g_ms->prompt->i_list]);
	}
	dummy = set_to_string(dummy);
	return (dummy);
}

char	*restart_to_string(char *newstr, char *dummy, int set)
{
	if (set == 1)
	{
		g_ms->prompt->i = 0;
		g_ms->prompt->j = 0;
		newstr = NULL;
		newstr = ft_calloc(ft_strlen(dummy), sizeof(char));
	}
	if (set == 2)
	{
		newstr[g_ms->prompt->i] = '\0';
		free(dummy);
		dummy = NULL;
	}
	return (newstr);
}

void	reset_list_values(char *dummy)
{
	g_ms->prompt->j = 0;
	g_ms->prompt->i = 0;
	g_ms->prompt->q_type = 0;
	g_ms->prompt->q_check = 0;
	g_ms->prompt->q_bool_envar = 0;
	ft_printf("%0.0s", dummy);
	free(dummy);
	dummy = NULL;
}

int	do_check(char *newstr2, int j, char *dummy)
{
	if (dummy[j + 1] != '\0')
		if (!ft_isalnum(dummy[j + 1]) || dummy[j + 1] != '?')
			j++;
	g_ms->prompt->j = j;
	g_ms->prompt->i = ft_strlen(newstr2);
	if (g_ms->prompt->i == 0 && g_ms->prompt->q_check == 1)
		newstr2[g_ms->prompt->i] = '\0';
	if (g_ms->prompt->q_check == 0 && newstr2[0] == '\0')
		g_ms->prompt->q_bool_envar = 1;
	return (j);
}
