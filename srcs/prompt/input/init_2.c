/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 14:16:10 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/25 14:11:50 by rverscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <signal.h>
#include <unistd.h>

void	init_prompt_loop(_Bool *flag_arrow1, _Bool *flag_arrow2,
					  						void (*enableRaw)())
{
	g_ms->history->counter = 0;
	if (g_ms->prompt->exec->flag == 1)
		free_exec();
	g_ms->prompt->line_flag = 0;
	g_ms->prompt->line_flag = 1;
	g_ms->prompt->pipe_count = 0;
	dup2(g_ms->prompt->stdoutfd, 1);
	dup2(g_ms->prompt->stdoutfd, 0);
	ft_putstr_fd(g_ms->prompt->line_start, 2);
	enableRaw();
	g_ms->prompt->line = ft_strdup("");
	g_ms->history->counter = g_ms->history->len;
	g_ms->history->cur_pos = 1;
	*flag_arrow1 = FALSE;
	*flag_arrow2 = FALSE;
}

void	init_prompt(void)
{
	t_prompt	prompt;
	t_exec		exec;
	t_term		term;

	g_ms->prompt = &prompt;
	g_ms->term = &term;
	g_ms->prompt->line_start = "ts -> ";
	g_ms->prompt->line_start = "";
	g_ms->prompt->quote = "'";
	g_ms->prompt->db_quote = '"';
	g_ms->prompt->red_fd = 0;
	g_ms->prompt->last_exit_code = 0;
	g_ms->prompt->envi = NULL;
	g_ms->prompt->pipe_count = 0;
	g_ms->prompt->bslashflag = 0;
	g_ms->prompt->stdinfd = dup(STDIN_FILENO);
	g_ms->prompt->stdoutfd = dup(STDOUT_FILENO);
	g_ms->prompt->exec = &exec;
	g_ms->prompt->pid = 0;
	init_prompt_2();
	set_env();
	signal(SIGQUIT, sigquithandler);
	signal(SIGINT, siginthandler);
	populate_commands();
	init_history();
}

void	init_prompt_3(void)
{
	t_presplits	**arr;
	char		**splits;
	int			ret;
	int			j;

	splits = NULL;
	arr = NULL;
	j = 0;
	g_ms->prompt->argslist = NULL;
	clean_calc_values();
	ret = 1;
	prompt_loop(arr, splits, ret, j);
}
