/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 16:43:46 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/13 00:12:53 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <input.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void	check_redirection(void)
{
	t_list	*current;
	char	*temp;

	current = g_ms->prompt->argslist;
	while (current->next != NULL)
	{
		temp = ft_strdup(current->content);
		if (ft_strequals(temp, ">"))
		{
			right_one(current, temp);
			break ;
		}
		else if (ft_strncmp(temp, ">>", 2) == 0 && ft_strlen(temp) == 2)
		{
			right_two(current, temp);
			break ;
		}
		else if (ft_strequals(temp, "<"))
		{
			left_one(current, temp);
			break ;
		}
		current = current->next;
		free(temp);
	}
}

static int	check_exit2(int i)
{
	check_redirection();
	while (i < CMD_AMOUNT)
	{
		if (ft_strncmp(g_ms->prompt->argslist->content,
				g_ms->prompt->commands[i].name,
				ft_strlen(g_ms->prompt->argslist->content)) == 0
			&& ft_strlen(g_ms->prompt->argslist->content)
			   == ft_strlen(g_ms->prompt->commands[i].name))
		{
			g_ms->prompt->commands[i].f();
			g_ms->prompt->last_exit_code = 0;
		}
		i++;
	}
	return (0);
}

int	check_exit(void)
{
	int	i;

	i = 0;
	if (g_ms->prompt->pipe_size < 2)
	{
		if ((ft_strequals(g_ms->prompt->argslist->content, "exit")
				|| ft_strequals(g_ms->prompt->argslist->content, "unset")
				|| ft_strequals(g_ms->prompt->argslist->content, "export")
				|| ft_strequals(g_ms->prompt->argslist->content, "env")
				|| ft_strequals(g_ms->prompt->argslist->content, "cd")))
			return (check_exit2(i));
	}
	return (1);
}

static void	pipe_loop2(int j, int a)
{
	if (j <= a && a != 1 && a != j)
		g_ms->prompt->has_pipe = 1;
	else
		g_ms->prompt->has_pipe = 0;
	if (g_ms->prompt->argslist != NULL)
		handle_command();
	if (g_ms->prompt->red_fd != 0)
		resume_output();
	if (g_ms->prompt->argslist != NULL)
	{
		ft_lstclear(&g_ms->prompt->argslist, &free_content);
		free(g_ms->prompt->argslist);
	}
	if (g_ms->prompt->has_pipe == 0 && g_ms->prompt->line != NULL)
	{
		free(g_ms->prompt->line);
		g_ms->prompt->line = NULL;
	}
}

void	pipe_loop(t_presplits **arr, int i, int j)
{
	t_list	*newlist;
	int		k;

	k = 0;
	newlist = NULL;
	g_ms->prompt->argv = arr[i]->argv;
	g_ms->prompt->args = arr[i]->argc;
	newlist = populate_list(newlist);
	pipe_loop2(j, arr[i]->pipe_size);
	while (k < arr[i]->argv)
	{
		free(arr[i]->argc[k]);
		arr[i]->argc[k] = NULL;
		k++;
	}
	free (arr[i]->argc);
	arr[i]->argc = NULL;
	g_ms->prompt->argv = 0;
}
