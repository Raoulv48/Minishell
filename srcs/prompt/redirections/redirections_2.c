/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections_2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 14:16:47 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 14:16:48 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <unistd.h>
#include <fcntl.h>

void	redirect_into(char *path)
{
	int	fd;

	g_ms->prompt->red_fd = dup(STDIN_FILENO);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		g_ms->prompt->red_fd = -1;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_output_to_pipe(void)
{
	close(g_ms->prompt->pipes[g_ms->prompt->pipe_count - 1].pipe[0]);
	dup2(g_ms->prompt->pipes[g_ms->prompt->pipe_count - 1].pipe[1],
		STDOUT_FILENO);
	close(g_ms->prompt->pipes[g_ms->prompt->pipe_count - 1].pipe[1]);
}

void	redirect_pipe_to_input(void)
{
	close(g_ms->prompt->pipes[g_ms->prompt->pipe_count - 2].pipe[1]);
	dup2(g_ms->prompt->pipes[g_ms->prompt->pipe_count - 2].pipe[0],
		STDIN_FILENO);
	close(g_ms->prompt->pipes[g_ms->prompt->pipe_count - 2].pipe[0]);
}

/*
** Resume the output on the stdin file descriptor (0) from
** g_ms->prompt->stdinfd. A copy of the STDIN fd is always saved here!
*/

void	resume_output2(void)
{
	dup2(g_ms->prompt->stdinfd, STDIN_FILENO);
	close(g_ms->prompt->red_fd2);
	g_ms->prompt->red_fd2 = 0;
}
