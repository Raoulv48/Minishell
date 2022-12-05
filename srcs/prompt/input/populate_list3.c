/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   populate_list3.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverscho <rverscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/30 18:43:18 by rverscho      #+#    #+#                 */
/*   Updated: 2021/05/20 13:14:10 by rverscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>

void	set_check(const char *s, int i)
{
	if (g_ms->prompt->q_check == 0)
	{
		if (s[i] == g_ms->prompt->quote[0])
			g_ms->prompt->q_type = 1;
		if (s[i] == g_ms->prompt->db_quote)
			g_ms->prompt->q_type = 2;
	}
	if (s[i] == g_ms->prompt->quote[0] && g_ms->prompt->q_type == 1
		&& g_ms->prompt->q_check == 0)
		g_ms->prompt->q_check = 1;
	else if (s[i] == g_ms->prompt->db_quote && g_ms->prompt->q_type == 2
		&& g_ms->prompt->q_check == 0)
		g_ms->prompt->q_check = 1;
	else if (g_ms->prompt->q_check == 1 && s[i] == g_ms->prompt->quote[0]
		&& g_ms->prompt->q_type == 1)
		g_ms->prompt->q_check = 0;
	else if (g_ms->prompt->q_check == 1 && s[i] == g_ms->prompt->db_quote
		&& g_ms->prompt->q_type == 2)
		g_ms->prompt->q_check = 0;
}

static char	add_char(char a)
{
	g_ms->prompt->i++;
	g_ms->prompt->j++;
	return (a);
}

char	*add_char_to_string(char *dummy, char *newstr)
{
	set_check(dummy, g_ms->prompt->j);
	if (dummy[g_ms->prompt->j] == ' ' && g_ms->prompt->q_check == 0)
		g_ms->prompt->j++;
	else if ((dummy[g_ms->prompt->j] == ';' && g_ms->prompt->q_check == 0)
		|| (dummy[g_ms->prompt->j] == ';' && dummy[g_ms->prompt->j + 1] == '\0'))
		g_ms->prompt->j++;
	else if ((dummy[g_ms->prompt->j] != '\0' && dummy[g_ms->prompt->j] != '\''
			&& dummy[g_ms->prompt->j] != '\"'))
		newstr[g_ms->prompt->i - 1] = add_char(dummy[g_ms->prompt->j]);
	else if ((dummy[g_ms->prompt->j] == '\'' && g_ms->prompt->q_type == 2)
		|| (dummy[g_ms->prompt->j] == '\"' && g_ms->prompt->q_type == 1))
		newstr[g_ms->prompt->i - 1] = add_char(dummy[g_ms->prompt->j]);
	else if ((dummy[g_ms->prompt->j] == '\'' && g_ms->prompt->q_type == 1)
		|| (dummy[g_ms->prompt->j] == '\"' && g_ms->prompt->q_type == 2))
		g_ms->prompt->j++;
	else if (dummy[g_ms->prompt->j] == ' ' && g_ms->prompt->q_check == 1)
		newstr[g_ms->prompt->i - 1] = add_char(dummy[g_ms->prompt->j]);
	return (newstr);
}

char	*set_to_string(char *dummy)
{
	char	*newstr;

	newstr = ft_calloc(ft_strlen(dummy), sizeof(char));
	while (dummy[g_ms->prompt->j] != '\0' && g_ms->prompt->j
		< (int)ft_strlen(dummy))
	{
		if (dummy[g_ms->prompt->j] == '$' && dummy[g_ms->prompt->j + 1] == '\"')
			g_ms->prompt->j++;
		else if ((dummy[g_ms->prompt->j] == '$' && (g_ms->prompt->q_check == 0
					|| (g_ms->prompt->q_check == 1
						&& g_ms->prompt->q_type == 2))))
			newstr = add_rest_value(dummy, newstr, g_ms->prompt->j,
					g_ms->prompt->i);
		else if ((dummy[g_ms->prompt->j] == '<' || dummy[g_ms->prompt->j]
				== '>') && g_ms->prompt->q_check == 0)
		{
			dummy = add_redir(dummy, newstr, g_ms->prompt->j, g_ms->prompt->i);
			newstr = restart_to_string(newstr, dummy, 1);
		}
		else if (dummy[g_ms->prompt->j] != '\0')
			newstr = add_char_to_string(dummy, newstr);
	}
	return (restart_to_string(newstr, dummy, 2));
}

int	to_join(char *dummy)
{
	int	i;

	i = 0;
	g_ms->prompt->q_type = 0;
	g_ms->prompt->q_check = 0;
	while ((size_t)i < ft_strlen(dummy))
	{
		set_check(dummy, i);
		i++;
	}
	if (g_ms->prompt->q_check == 0)
	{
		g_ms->prompt->q_type = 0;
		g_ms->prompt->q_check = 0;
		return (0);
	}
	g_ms->prompt->q_type = 0;
	g_ms->prompt->q_check = 0;
	return (1);
}
