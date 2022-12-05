/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:02:10 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 14:20:34 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>
#include <prompt.h>
#include <string.h>
#include <errno.h>

static void	update_oldpwd(char *env, int len, char *oldpath)
{
	t_list	*cur;
	char	*temp;
	char	*res;

	cur = g_ms->prompt->envi;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->content, env, len) == 0)
		{
			temp = ft_substr(cur->content, 0, len);
			res = ft_strjoin(temp, oldpath);
			free(oldpath);
			free(cur->content);
			cur->content = ft_strdup(res);
			free(res);
			break ;
		}
		cur = cur->next;
	}
}

static char	*get_oldpwd(void)
{
	t_list	*cur;
	char	*res;

	cur = g_ms->prompt->envi;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->content, "OLDPWD=", 7) == 0)
		{
			res = ft_substr(cur->content, 7, ft_strlen(cur->content));
			return (res);
		}
		cur = cur->next;
	}
	return (NULL);
}

static void	check(t_list *path, char *oldpath)
{
	if (path == NULL)
		ft_dprintf(2, "cd: Expected atleast 1 argument\n");
	else if (path->next != NULL)
	{
		ft_dprintf(2, "cd: Too many arguments!\n");
		g_ms->prompt->last_exit_code = 1;
	}
	else if (chdir(path->content) != 0)
	{
		ft_dprintf(2, "cd: Unable to navigate to: %s\n", path->content);
		g_ms->prompt->last_exit_code = 1;
		free(oldpath);
	}
	else
	{
		update_oldpwd("OLDPWD=", 7, oldpath);
		update_oldpwd("PWD=", 4, getcwd(NULL, 0));
	}
}

void	cd(void)
{
	t_list	*path;
	char	*oldpath;
	char	*temp;

	path = g_ms->prompt->argslist->next;
	oldpath = getcwd(NULL, 0);
	if (ft_strequals(path->content, "-"))
	{
		free(path->content);
		temp = get_oldpwd();
		path->content = ft_strdup(temp);
		free(temp);
		ft_printf("%s\n", path->content);
	}
	check(path, oldpath);
}
