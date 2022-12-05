/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calc_argv.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:36:56 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/21 14:18:55 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <builtins.h>
#include <prompt.h>
#include <stdlib.h>

int	calc_argv(const char *s, int c)
{
	int		i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != '\0')
		{
			count++;
		}
		i++;
	}
	return (count + 1);
}

static int	free_and_return(char *str, char *str1, int count)
{
	free(str);
	free(str1);
	return (count + 1);
}

int	pipe_error_handler(const char *s, int count, int ks)
{
	int		i;
	int		j;
	char	*str;
	char	*str1;

	i = 0;
	while (s[i] != '|' && s[i] != '\0')
		i++;
	j = i + 1;
	while (s[j] != '|' && s[j] != '\0')
		j++;
	str = ft_substr(s, i, j - i);
	str1 = ft_substr (s, 0, i);
	if ((ft_str_only_contains(str, "| ") || (s[0] == '|')
			|| (s[ks] == '|')) && (ft_str_only_contains(str1, "| ")))
	{
		ft_dprintf(2, "%s: syntax error near unexpected token `|'\n",
			g_ms->prog_name);
		return (0);
	}
	if (!ft_str_only_contains(str, "| ") && !ft_str_only_contains(str1, "| "))
		return (free_and_return(str, str1, count));
	free_and_return(str, str1, count);
	return (0);
}

static void	calc_argv_sc_while(const char *s, int c, int *i, size_t *count)
{
	while (s[*i] != '\0')
	{
		set_check(s, *i);
		if (s[*i] == c && g_ms->prompt->q_check != 1)
			*count = *count + 1;
		*i = *i + 1;
	}
}

int	calc_argv_sc(const char *s, int c)
{
	int		i;
	size_t	count;
	int		ks;

	g_ms->prompt->q_check = 0;
	count = 0;
	i = 0;
	ks = 0;
	calc_argv_sc_while(s, c, &i, &count);
	if (s[i - 1] == c && (c == ';' || (c == ' ')))
		count--;
	g_ms->prompt->q_check = 0;
	g_ms->prompt->q_type = 0;
	if (c == '|')
	{
		while (s[ks] == ' ')
			ks++;
		if (count > 0 || s[ks] == '|'
			|| ft_str_only_contains((char *)s, " |"))
			return (pipe_error_handler(s, count, ks));
	}
	return (count + 1);
}
