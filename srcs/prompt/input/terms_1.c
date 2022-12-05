/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terms_1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 14:16:36 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 14:16:37 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>
#include <unistd.h>

static void	backspace(_Bool *flag_arrow1, _Bool *flag_arrow2, void (*clear)())
{
	char	*temp;
	char	*temp2;
	int		k;

	if (g_ms->history->cur_pos > 1)
	{
		temp = ft_substr(g_ms->prompt->line, g_ms->history->cur_pos - 1,
				   ft_strlen(g_ms->prompt->line));
		temp2 = ft_substr(g_ms->prompt->line, 0, g_ms->history->cur_pos - 2);
		free(g_ms->prompt->line);
		g_ms->prompt->line = ft_strjoin(temp2, temp);
		free(temp);
		clear();
		ft_printf("\r%s%s", g_ms->prompt->line_start, g_ms->prompt->line);
		k = ft_strlen(g_ms->prompt->line);
		while (k > g_ms->history->cur_pos - 2)
		{
			ft_printf("\033[D");
			k--;
		}
		g_ms->history->cur_pos--;
		*flag_arrow1 = FALSE;
		*flag_arrow2 = FALSE;
	}
}

static void	arrow_up(_Bool *flag_arrow1, _Bool *flag_arrow2, void (*clear)(),
					 								void (*add_history)(_Bool))
{
	if (g_ms->history->counter >= 1)
	{
		if (g_ms->history->counter == g_ms->history->len)
			add_history(TRUE);
		if (g_ms->prompt->line != NULL)
			free(g_ms->prompt->line);
		g_ms->prompt->line = ft_strdup(
				g_ms->history->history[g_ms->history->counter - 1]);
		g_ms->history->counter--;
		clear();
		g_ms->history->cur_pos = ft_strlen(g_ms->prompt->line) + 1;
		ft_printf("\r%s%s", g_ms->prompt->line_start, g_ms->prompt->line);
		*flag_arrow1 = FALSE;
		*flag_arrow2 = FALSE;
	}
}

static void	arrow_down(_Bool *flag_arrow1, _Bool *flag_arrow2, void (*clear)())
{
	if (g_ms->history->counter < g_ms->history->len - 1)
	{
		if (g_ms->prompt->line != NULL)
			free(g_ms->prompt->line);
		g_ms->prompt->line = ft_strdup(
				g_ms->history->history[g_ms->history->counter + 1]);
		g_ms->history->counter++;
		clear();
		g_ms->history->cur_pos = ft_strlen(g_ms->prompt->line) + 1;
		ft_printf("\r%s%s", g_ms->prompt->line_start, g_ms->prompt->line);
		*flag_arrow1 = FALSE;
		*flag_arrow2 = FALSE;
	}
}

static void	append_line(char c, _Bool *flag_arrow1, _Bool *flag_arrow2,
														void (*clear)())
{
	char	*str;
	int		k;

	str = malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	g_ms->prompt->line = ft_strjoin(g_ms->prompt->line, str);
	free(str);
	str = NULL;
	clear();
	ft_dprintf(STDIN_FILENO, "%s", g_ms->prompt->line);
	k = ft_strlen(g_ms->prompt->line);
	while (k > g_ms->history->cur_pos)
	{
		ft_printf("\033[D");
		k--;
	}
	g_ms->history->cur_pos++;
	*flag_arrow1 = FALSE;
	*flag_arrow2 = FALSE;
}

void	handle_input(_Bool *flag_arrow1, _Bool *flag_arrow2,
				  		void (*clear), void (*add_history)(_Bool))
{
	if (g_ms->prompt->c == BACKSPACE)
		backspace(flag_arrow1, flag_arrow2, clear);
	else if (g_ms->prompt->c == ARROW_UP && *flag_arrow2 == TRUE)
		arrow_up(flag_arrow1, flag_arrow2, clear, add_history);
	else if (g_ms->prompt->c == ARROW_DOWN && *flag_arrow2 == TRUE)
		arrow_down(flag_arrow1, flag_arrow2, clear);
	else if (g_ms->prompt->c != 27 && g_ms->prompt->c != 91 && g_ms->prompt->c
		!= BACKSPACE && *flag_arrow2 == FALSE)
		append_line(g_ms->prompt->c, flag_arrow1, flag_arrow2, clear);
}
