/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   populate_commands.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 19:58:41 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <stdlib.h>

void	populate_commands(void)
{
	g_ms->prompt->commands = malloc(sizeof(t_commands) * CMD_AMOUNT);
	g_ms->prompt->commands[0].name = "exit";
	g_ms->prompt->commands[0].f = &exit_ms;
	g_ms->prompt->commands[1].name = "cd";
	g_ms->prompt->commands[1].f = &cd;
	g_ms->prompt->commands[2].name = "pwd";
	g_ms->prompt->commands[2].f = &pwd;
	g_ms->prompt->commands[3].name = "echo";
	g_ms->prompt->commands[3].f = &echo;
	g_ms->prompt->commands[4].name = "unset";
	g_ms->prompt->commands[4].f = &unset;
	g_ms->prompt->commands[5].name = "env";
	g_ms->prompt->commands[5].f = &env;
	g_ms->prompt->commands[6].name = "export";
	g_ms->prompt->commands[6].f = &export_function;
	g_ms->prompt->commands[7].name = "clear";
	g_ms->prompt->commands[7].f = &clean;
	g_ms->prompt->commands[8].name = "help";
	g_ms->prompt->commands[8].f = &help_cmd;
	g_ms->prompt->commands[9].name = "mad";
	g_ms->prompt->commands[9].f = &mad;
}
