/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_5.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:58:43 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 20:58:44 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>
#include <unistd.h>
#include <builtins.h>

void	free_content(void *arg)
{
	free(arg);
}

int	get_prompt_loop_data3(_Bool flag)
{
	if (flag == TRUE)
	{
		if (g_ms->prompt->pipe_size != 1)
			g_ms->prompt->pipes = malloc(sizeof(t_pipes)
					* g_ms->prompt->pipe_size);
	}
	else
	{
		if (g_ms->prompt->line != NULL)
			free(g_ms->prompt->line);
		g_ms->prompt->line = NULL;
	}
	return (0);
}

t_presplits	**get_prompt_loop_data2(t_presplits **arr, int i, char **splits)
{
	dup2(g_ms->prompt->stdoutfd, 1);
	dup2(g_ms->prompt->stdoutfd, 0);
	g_ms->prompt->pipe_count = 0;
	arr[i] = malloc(sizeof(t_presplits));
	arr[i]->pipe_size = calc_argv_sc(splits[i], '|');
	clean_calc_values();
	arr[i]->split_pipe = ft_split_sc(splits[i], '|');
	clean_calc_values();
	g_ms->prompt->pipe_size = arr[i]->pipe_size;
	return (arr);
}

void	get_prompt_loop_data(int i, int j, t_presplits **arr, char **splits)
{
	g_ms->prompt->sc_size = calc_argv_sc(g_ms->prompt->line, ';');
	if (g_ms->prompt->sc_size == 0)
		g_ms->prompt->sc_size = 1;
	clean_calc_values();
	arr = malloc(sizeof(t_presplits *) * g_ms->prompt->sc_size);
	ft_bzero(arr, sizeof(t_presplits *));
	splits = ft_split_sc(g_ms->prompt->line, ';');
	clean_calc_values();
	i = 0;
	while (i < g_ms->prompt->sc_size && splits[i] != NULL)
	{
		arr = get_prompt_loop_data2(arr, i, splits);
		if (g_ms->prompt->pipes != NULL)
			free(g_ms->prompt->pipes);
		g_ms->prompt->pipes = NULL;
		j = get_prompt_loop_data3(TRUE);
		free(splits[i]);
		splits[i] = NULL;
		fill_prompt(i, j, arr);
		i = free_prompt_loop_1(i, j, arr);
	}
	free_prompt_loop_2(i, arr, splits);
	get_prompt_loop_data3(FALSE);
}
