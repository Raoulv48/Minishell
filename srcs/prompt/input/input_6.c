/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_6.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 21:20:46 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 21:20:47 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

static int	handle_command5(pid_t wpid, int status)
{
	wpid = waitpid(g_ms->prompt->pid, &status, WUNTRACED);
	if (g_ms->prompt->pipe_size > 1)
	{
		if (g_ms->prompt->pipe_size == g_ms->prompt->pipe_count)
			close(g_ms->prompt->pipes[g_ms->prompt->pipe_count
				- 1].pipe[0]);
		else if (g_ms->prompt->pipe_count > 1)
			close(g_ms->prompt->pipes[g_ms->prompt->pipe_count
				- 2].pipe[0]);
		close(g_ms->prompt->pipes[g_ms->prompt->pipe_count
			- 1].pipe[1]);
		dup2(g_ms->prompt->stdoutfd, 1);
		dup2(g_ms->prompt->stdoutfd, 0);
	}
	if (g_ms->prompt->red_fd != 0)
		resume_output();
	if (g_ms->prompt->red_fd2 != 0)
		resume_output2();
	return (status);
}

static void	handle_command4(int i)
{
	while (i < CMD_AMOUNT)
	{
		if (ft_strncmp(g_ms->prompt->argslist->content,
				g_ms->prompt->commands[i].name,
				ft_strlen(g_ms->prompt->argslist->content)) == 0
			&& ft_strlen(g_ms->prompt->argslist->content)
			   == ft_strlen(g_ms->prompt->commands[i].name))
		{
			g_ms->prompt->commands[i].f();
			exit(0);
		}
		i++;
	}
}

static void	handle_command3(int i)
{
	if (g_ms->prompt->pipe_count < g_ms->prompt->pipe_size)
		redirect_output_to_pipe();
	if (g_ms->prompt->pipe_count > 1
		&& g_ms->prompt->pipe_count <= g_ms->prompt->pipe_size)
		redirect_pipe_to_input();
	signal(SIGSEGV, sigsegvhandler);
	check_redirection();
	handle_command4(i);
	if (ft_strcontains(g_ms->prompt->argslist->content, "/"))
	{
		is_exec();
		exit(g_ms->prompt->last_exit_code);
	}
	else if (is_existing_exec() == 0)
	{
		if (g_ms->prompt->argslist->content != NULL)
			ft_dprintf(2, "%s: %s: command not found\n",
				g_ms->prog_name, g_ms->prompt->argslist->content);
		exit(127);
	}
	exit(1);
}

static void	handle_command2(int i, pid_t wpid, int status)
{
	g_ms->prompt->pid = fork();
	i = 0;
	if (g_ms->prompt->pid == 0)
		handle_command3(i);
	else if (g_ms->prompt->pid < 0)
		ft_dprintf(2, "%s\n", strerror(errno));
	else
		status = handle_command5(wpid, status);
	if (WIFEXITED(status))
		g_ms->prompt->last_exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_ms->prompt->last_exit_code = WTERMSIG(status);
		g_ms->prompt->last_exit_code += WCOREDUMP(status);
	}
}

void	handle_command(void)
{
	int		i;
	int		status;
	pid_t	wpid;

	status = -1;
	i = 0;
	wpid = (pid_t) NULL;
	g_ms->prompt->pipe_count++;
	if (g_ms->prompt->pipe_count < g_ms->prompt->pipe_size)
		pipe(g_ms->prompt->pipes[g_ms->prompt->pipe_count - 1].pipe);
	if (g_ms->prompt->has_pipe == 0 && !check_exit())
		;
	else
		handle_command2(i, wpid, status);
	g_ms->prompt->pid = 0;
}
