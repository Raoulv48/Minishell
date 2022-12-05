/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 16:45:28 by jlensing      #+#    #+#                 */
/*   Updated: 2021/04/06 19:05:29 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>
#include <termcap.h>

void	set_shlvl(char *env)
{
	char	*temp;
	char	*temp2;
	char	*res;
	int		i;
	t_list	*newlist;

	temp = ft_substr(env, 6, ft_strlen(temp));
	temp2 = ft_substr(env, 0, 6);
	i = ft_atoi(temp);
	free(temp);
	i++;
	temp = ft_itoa(i);
	res = ft_strjoin(temp2, temp);
	free(temp);
	newlist = ft_lstnew(ft_strdup(res));
	ft_lstadd_back(&g_ms->prompt->envi, newlist);
	free(res);
}

void	set_env(void)
{
	extern char	**environ;
	int			i;
	t_list		*newlist;

	i = 0;
	g_ms->prompt->last_exit_code = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "SHLVL=", 6) == 0)
			set_shlvl(environ[i]);
		else
		{
			newlist = ft_lstnew(ft_strdup(environ[i]));
			ft_lstadd_back(&g_ms->prompt->envi, newlist);
		}
		i++;
	}
}

static void	init_term(void)
{
	char	buff[3];	

	tgetent(buff, getenv("TERM"));
	g_ms->term->width = tgetnum("co");
	g_ms->term->height = tgetnum("li");
	g_ms->term->cur_line = 0;
}

void	init_prompt_2(void)
{
	g_ms->prompt->exec->flag = 0;
	g_ms->prompt->q_check = 0;
	g_ms->prompt->q_type = 0;
	g_ms->prompt->i = 0;
	g_ms->prompt->j = 0;
	g_ms->prompt->one_space = 0;
	g_ms->prompt->pipes = NULL;
	init_term();
}

void	init_history(void)
{
	t_history	history;

	g_ms->history = &history;
	g_ms->history->history = NULL;
	g_ms->history->counter = 0;
	g_ms->history->len = 0;
	g_ms->history->cur_pos = 0;
	init_prompt_3();
}
