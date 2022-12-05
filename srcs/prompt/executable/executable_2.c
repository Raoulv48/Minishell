/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:58:29 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 20:58:30 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void	free_exec(void)
{
	int	i;

	i = 0;
	while (g_ms->prompt->exec->args[i] != NULL)
	{
		free(g_ms->prompt->exec->args[i]);
		i++;
	}
	free(g_ms->prompt->exec->args);
	i = 0;
	while (g_ms->prompt->exec->env[i] != NULL)
	{
		free(g_ms->prompt->exec->env[i]);
		i++;
	}
	free(g_ms->prompt->exec->env);
	g_ms->prompt->exec->flag = 0;
}

char	**return_env(void)
{
	char	**ret;
	int		size;
	t_list	*cur;
	int		i;

	size = ft_lstsize(g_ms->prompt->envi);
	ret = malloc(sizeof(char *) * size + 1);
	cur = g_ms->prompt->envi;
	i = 0;
	while (cur != NULL)
	{
		ret[i] = ft_strdup(cur->content);
		i++;
		cur = cur->next;
	}
	ret[i] = NULL;
	return (ret);
}

int	get_list_size(t_list *list)
{
	int		i;
	t_list	*cur;

	cur = list;
	i = 0;
	while (cur != NULL)
	{
		if (ft_str_only_contains(cur->content, ">")
			|| ft_str_only_contains(cur->content, "<")
			|| ft_str_only_contains(cur->content, ">>"))
			break ;
		i++;
		cur = cur->next;
	}
	return (i);
}

char	**return_args(void)
{
	char	**ret;
	t_list	*cur;
	int		i;

	ret = malloc(sizeof(char *) * get_list_size(
				g_ms->prompt->argslist) + 1);
	cur = g_ms->prompt->argslist;
	i = 0;
	while (cur != NULL)
	{
		if (ft_str_only_contains(cur->content, ">")
			|| ft_str_only_contains(cur->content, "<")
			|| ft_str_only_contains(cur->content, ">>"))
			break ;
		ret[i] = ft_strdup(cur->content);
		i++;
		cur = cur->next;
	}
	if (g_ms->prompt->red_fd == -1)
	{
		ret[i] = ft_strtrim(ft_strdup(cur->next->content), " ");
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	execute_cmd(void)
{
	int	ret;

	g_ms->prompt->exec->args = return_args();
	g_ms->prompt->exec->env = return_env();
	g_ms->prompt->exec->flag = 1;
	ret = execve(g_ms->prompt->argslist->content,
			  (char *const *)g_ms->prompt->exec->args,
			  (char *const *)g_ms->prompt->exec->env);
	if (ret < 0)
		ft_dprintf(2, "%s\n", strerror(errno));
}
