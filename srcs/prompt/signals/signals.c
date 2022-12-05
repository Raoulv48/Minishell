/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 23:36:24 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/21 14:24:06 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <libft.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <builtins.h>

void	siginthandler(int sig)
{
	signal(SIGINT, siginthandler);
	dup2(g_ms->prompt->stdoutfd, 1);
	dup2(g_ms->prompt->stdoutfd, 0);
	if (g_ms->prompt->pid <= 0)
		ft_printf("\n%s", g_ms->prompt->line_start);
	else
	{
		ft_putstr_fd("\n", 1);
		kill(g_ms->prompt->pid, SIGTERM);
		g_ms->prompt->last_exit_code = 130;
	}
	if (g_ms->prompt->line != NULL)
	{
		free(g_ms->prompt->line);
		g_ms->prompt->line = ft_strdup("");
	}
	g_ms->prompt->pid = 0;
	sig = 2;
}

void	sigquithandler(int sig)
{
	signal(SIGQUIT, sigquithandler);
	if (g_ms->prompt->pid > 0)
	{
		ft_printf("Quit: %d\n", sig);
		kill(g_ms->prompt->pid, SIGQUIT);
		g_ms->prompt->last_exit_code = 131;
		g_ms->prompt->pid = 0;
	}
}

void	sigsegvhandler(int sig)
{
	ft_dprintf(2, "An segfault (%d) occured,", sig);
	ft_dprintf(2, " please try again.\n");
	exit(11);
}
