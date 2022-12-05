/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 17:43:23 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <prompt.h>
#include <libft.h>

/*
** This will replace fd 1 with the normal STDOUT that is saved within
** g_ms->prompt->stdoutfd. A copy of the STDOUT fd is always saved here!
*/

void	resume_output(void)
{
	dup2(g_ms->prompt->stdoutfd, STDOUT_FILENO);
	close(g_ms->prompt->red_fd);
	g_ms->prompt->red_fd = 0;
}

/*
** Create a new file or overwrite the file if it already exists
** then move the new file descriptor onto STDOUT (1)
** this currently propably leaks the red_fd file descriptors
*/

static int	get_index(void)
{
	int		i;
	t_list	*cur;

	i = 0;
	cur = g_ms->prompt->argslist;
	while (cur != NULL)
	{
		if (ft_strequals(">", cur->content)
			|| ft_strequals(">>", cur->content)
			|| ft_strequals("<", cur->content))
			return (i);
		i++;
		cur = cur->next;
	}
	return (-1);
}

static void	remove_symbols_and_path(void)
{
	int	index;
	int	temp;

	temp = 1;
	index = get_index();
	while (ft_strequals(ft_get_lst_content(g_ms->prompt->argslist,
				index + temp), ""))
		temp++;
	while (temp >= 0)
	{
		if (ft_get_lst_content(g_ms->prompt->argslist, index + temp) != NULL)
			ft_del_lst_index(g_ms->prompt->argslist, index + temp);
		temp--;
	}
}

void	redirect_new(char *path)
{
	int	fd;

	g_ms->prompt->red_fd = dup(STDOUT_FILENO);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	remove_symbols_and_path();
}

/*
** Same as the function above only instead of creating a new file/overwriting
** it will append to the file that has been loaded
*/

void	redirect_append(char *path)
{
	int	fd;

	g_ms->prompt->red_fd = dup(STDOUT_FILENO);
	fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	remove_symbols_and_path();
}

/*
** This will redirect the file given to it by path and send it to stdin
*/
