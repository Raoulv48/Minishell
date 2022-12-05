/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terms_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverscho <rverscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 15:43:45 by rverscho      #+#    #+#                 */
/*   Updated: 2021/05/20 16:02:53 by rverscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>

_Bool	check_pipes_only(void)
{
	if (ft_str_only_contains(g_ms->prompt->line, "| ")
		|| handler(g_ms->prompt->line, '|', 0) == -1)
	{
		ft_dprintf(2, "%s: syntax error near unexpected token `|'\n",
			 g_ms->prog_name);
		free(g_ms->prompt->line);
		g_ms->prompt->last_exit_code = 258;
		return (TRUE);
	}
	return (FALSE);
}

_Bool	check_semicolumn_only(void)
{
	if (ft_str_only_contains(g_ms->prompt->line, "; ")
		|| handler(g_ms->prompt->line, ';', 0) == -1)
	{
		ft_dprintf(2, "%s: syntax error near unexpected token `;'\n",
			g_ms->prog_name);
		free(g_ms->prompt->line);
		g_ms->prompt->last_exit_code = 258;
		return (TRUE);
	}
	return (FALSE);
}

_Bool	check_empty(void)
{
	if (ft_strlen(g_ms->prompt->line) == 0
		|| ft_str_only_contains(g_ms->prompt->line, " "))
	{
		free(g_ms->prompt->line);
		return (TRUE);
	}
	return (FALSE);
}

_Bool	check_return(char c)
{
	if (c == RETURN)
	{
		ft_printf("\n");
		return (TRUE);
	}
	return (FALSE);
}

void	reset_values_prompt(void (*disableRaw)(), void (*add_history)(_Bool))
{
	disableRaw();
	add_history(FALSE);
	g_ms->term->cur_line = 0;
}
