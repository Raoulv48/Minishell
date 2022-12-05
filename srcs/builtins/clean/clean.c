/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rverscho <rverscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 16:03:27 by rverscho      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <builtins.h>
#include <libft.h>
#include <stddef.h>
#include <stdlib.h>

void	clean(void)
{
	char	buff[3];
	char	*str;

	tgetent(buff, getenv("TERM"));
	str = tgetstr("cl", NULL);
	ft_printf("%s", str);
}
