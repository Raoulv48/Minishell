/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 17:01:38 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 15:58:31 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <stdlib.h>

static void	free_content(void *arg)
{
	free(arg);
}

static void	free_history(void)
{
	int	i;

	i = g_ms->history->len - 1;
	while (i >= 0)
	{
		free(g_ms->history->history[i]);
		i--;
	}
	free (g_ms->history->history);
}

static void	free_end(void)
{
	free(g_ms->prompt->args);
	free (g_ms->prompt->commands);
	ft_lstclear(&g_ms->prompt->envi, &free_content);
	free (g_ms->prog_name);
	if (g_ms->prompt->pipes != NULL)
		free(g_ms->prompt->pipes);
	g_ms->prompt->pipes = NULL;
	free(g_ms);
	g_ms = NULL;
}

static int	set_exit_code(void)
{
	int	exit_code;

	exit_code = 0;
	if (g_ms->prompt->argslist != NULL)
	{
		if (g_ms->prompt->argslist->next != NULL)
		{
			if (ft_str_only_contains(g_ms->prompt->argslist->next->content,
					"0123456789"))
				exit_code = ft_atoi(g_ms->prompt->argslist->next->content);
			else if (g_ms->prompt->argslist->next->next == NULL)
			{
				ft_dprintf(2, "%s: exit: %s: numeric argument required\n",
					g_ms->prog_name, g_ms->prompt->argslist->next->content);
				exit_code = 255;
			}
			else
				ft_dprintf(2, "%s: exit: too many arguments\n", g_ms->prog_name);
		}
	}
	return (exit_code);
}

void	exit_ms(void)
{
	int	exit_code;
	int	k;

	exit_code = 0;
	free_history();
	k = 0;
	if (g_ms->prompt->line != NULL)
		free(g_ms->prompt->line);
	exit_code = set_exit_code();
	if (g_ms->prompt->argslist != NULL)
		ft_lstclear(&g_ms->prompt->argslist, &free_content);
	while (k < g_ms->prompt->argv)
	{
		if (g_ms->prompt->args != NULL)
			free (g_ms->prompt->args[k]);
		k++;
	}
	free_end();
	if (exit_code > 255)
		exit_code = exit_code % 256;
	exit(exit_code);
}
