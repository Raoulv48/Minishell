/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_4.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:58:41 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 20:58:41 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <builtins.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

void	clean_calc_values(void)
{
	g_ms->prompt->q_type = 0;
	g_ms->prompt->q_check = 0;
}

int	free_prompt_loop_1(int i, int j, t_presplits **arr)
{
	j = 0;
	while (j < arr[i]->pipe_size)
	{
		free(arr[i]->split_pipe[j]);
		arr[i]->split_pipe[j] = NULL;
		j++;
	}
	i++;
	return (i);
}

void	free_prompt_loop_2(int i, t_presplits **arr, char **splits)
{
	i = 0;
	while (i < g_ms->prompt->sc_size)
	{
		free(arr[i]->split_pipe);
		arr[i]->split_pipe = NULL;
		if (arr[i] != NULL)
			free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(g_ms->prompt->pipes);
	g_ms->prompt->pipes = NULL;
	free(arr);
	arr = NULL;
	if (splits != NULL)
		free(splits);
	splits = NULL;
}

void	fill_prompt(int i, int j, t_presplits **arr)
{
	while (j < arr[i]->pipe_size)
	{
		g_ms->prompt->has_pipe = 0;
		if (arr[i]->split_pipe[j] != NULL)
		{
			if (ft_strlen(arr[i]->split_pipe[j]) > 1)
				arr[i]->split_pipe[j] = ft_strtrim(
						arr[i]->split_pipe[j], " ");
			arr[i]->argv = calc_argv_sc(arr[i]->split_pipe[j], ' ');
			clean_calc_values();
			arr[i]->argc = ft_split_2(arr[i]->split_pipe[j], ' ');
			clean_calc_values();
			pipe_loop(arr, i, j);
		}
		j++;
	}
}

void	check_exit_2(char c)
{
	if (c == 4 && ft_strlen(g_ms->prompt->line) == 0)
	{
		ft_dprintf(STDIN_FILENO, "exit\n");
		g_ms->prompt->args = NULL;
		exit_ms();
	}
}
