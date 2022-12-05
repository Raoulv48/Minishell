/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executable.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 00:55:56 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 20:10:27 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <libft.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <builtins.h>

int	is_exec(void)
{
	struct stat	stats;

	stat(g_ms->prompt->argslist->content, &stats);
	if (stats.st_mode & 0111)
	{
		execute_cmd();
		return (1);
	}
	g_ms->prompt->last_exit_code = 127;
	ft_dprintf(2, "%s: %s: No such file or directory\n",
		g_ms->prog_name, g_ms->prompt->argslist->content);
	return (0);
}

static t_path	get_path(void)
{
	t_path	path;
	t_list	*cur;
	char	*temp;

	cur = g_ms->prompt->envi;
	path.res = NULL;
	while (cur != NULL)
	{
		if (ft_strncmp(cur->content, "PATH=", 5) == 0)
		{
			temp = ft_substr(cur->content, 5, ft_strlen(cur->content));
			path.size = calc_argv(temp, ':');
			path.res = ft_split(temp, ':');
			if (path.size == 1)
				path.size += 1;
			free(temp);
			break ;
		}
		cur = cur->next;
	}
	return (path);
}

int	is_existing_exec3(t_execstruct exec)
{
	exec.i = 0;
	while (exec.i < exec.path.size - 2)
	{
		free(exec.path.res[exec.i]);
		exec.i++;
	}
	if (exec.flag == 1)
		return (is_exec());
	return (0);
}

t_execstruct	is_existing_exec2(t_execstruct exec)
{
	while (exec.file != NULL)
	{
		if (ft_strequals(exec.trimmedstr, exec.file->d_name))
		{
			ft_strlcat(exec.res, exec.file->d_name, ft_strlen(exec.res)
				+ ft_strlen(exec.file->d_name) + 1);
			g_ms->prompt->argslist->content = ft_strdup(exec.res);
			free(exec.res);
			exec.flag = 1;
			break ;
		}
		exec.file = readdir(exec.dir);
	}
	return (exec);
}

int	is_existing_exec(void)
{
	t_execstruct	exec;

	exec.flag = 0;
	exec.path = get_path();
	exec.i = 0;
	while (exec.i < exec.path.size)
	{
		exec.a = ft_strdup(exec.path.res[exec.i]);
		exec.dir = opendir(exec.a);
		if (exec.dir != NULL)
			exec.file = readdir(exec.dir);
		else
			exec.file = NULL;
		exec.res = ft_strjoin(exec.a, "/");
		exec.trimmedstr = ft_strdup(g_ms->prompt->argslist->content);
		exec = is_existing_exec2(exec);
		free(exec.trimmedstr);
		if (exec.dir != NULL)
			closedir(exec.dir);
		if (exec.flag == 1)
			break ;
		exec.i++;
	}
	return (is_existing_exec3(exec));
}
