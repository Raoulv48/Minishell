/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terms_4.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:58:58 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 20:58:59 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <prompt.h>
#include <unistd.h>

void	disableRaw(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_ms->prompt->orig_termios);
}

void	enableRaw(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &g_ms->prompt->orig_termios);
	raw = g_ms->prompt->orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
