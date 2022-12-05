/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 16:43:46 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 15:58:43 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <builtins.h>
#include <stdlib.h>
#include <unistd.h>
#include <termcap.h>

static void	clear_line(void)
{
	char	*str;

	str = tgetstr("cd", NULL);
	ft_printf("%c[%d;%df", 0x1B, g_ms->term->height - g_ms->term->cur_line, 0);
	ft_printf("%s", str);
}

static void	add_history(_Bool flag)
{
	char	**new_history;
	int		i;

	if (ft_strequals(g_ms->prompt->line, ""))
		return ;
	flag = FALSE;
	new_history = malloc(sizeof(char *) * g_ms->history->len + 1);
	i = 0;
	while (i < g_ms->history->len)
	{
		new_history[i] = ft_strdup(g_ms->history->history[i]);
		free (g_ms->history->history[i]);
		i++;
	}
	new_history[i] = ft_strdup(g_ms->prompt->line);
	g_ms->history->len++;
	if (g_ms->history->len != 0)
		free (g_ms->history->history);
	g_ms->history->history = new_history;
}

static void	read_loop2(_Bool *flag_arrow1, _Bool *flag_arrow2)
{
	if ((int)ft_strlen(g_ms->prompt->line)
		/ g_ms->term->width > g_ms->term->cur_line)
		g_ms->term->cur_line = ft_strlen(g_ms->prompt->line)
			/ g_ms->term->width;
	*flag_arrow1 = FALSE;
	*flag_arrow2 = FALSE;
}

void	read_loop(_Bool flag_arrow1, _Bool flag_arrow2, char c)
{
	while (read(STDIN_FILENO, &c, 1) == 1)
	{
		check_exit_2(c);
		if (c == 27)
		{
			flag_arrow1 = TRUE;
			continue ;
		}
		if (flag_arrow1 == TRUE && c == 91)
		{
			flag_arrow2 = TRUE;
			continue ;
		}
		if (check_return(c) == TRUE)
			break ;
		g_ms->prompt->c = c;
		handle_input(&flag_arrow1, &flag_arrow2, &clear_line, &add_history);
		if (ft_strcontains(g_ms->prompt->line, "\n"))
		{
			new_line(&flag_arrow1, &flag_arrow2);
			break ;
		}
		read_loop2(&flag_arrow1, &flag_arrow2);
	}
}

void	prompt_loop(t_presplits **arr, char **splits, int ret, int j)
{
	char		c;
	_Bool		flag_arrow1;
	_Bool		flag_arrow2;

	c = 0;
	while (ret > 0)
	{
		init_prompt_loop(&flag_arrow1, &flag_arrow2, &enableRaw);
		read_loop(flag_arrow1, flag_arrow2, c);
		if (check_empty() == TRUE || check_semicolumn_only() == TRUE
			|| check_pipes_only() == TRUE)
			continue ;
		reset_values_prompt(&disableRaw, &add_history);
		if (ft_strequals(g_ms->prompt->line, "\0"))
			continue ;
		get_prompt_loop_data(0, j, arr, splits);
	}
	g_ms->prompt->has_pipe = 0;
}
