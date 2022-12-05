/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:08:16 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <libft.h>
#include <unistd.h>
#include <stdlib.h>

/*
** Print our the path of the folder we are currently in if there is no argument
** Using getcwd() to get the path. I'm not sure why you would want to use a buff
** and size for getcwd to get the path since we always get the full path and
** this is returned by the function in the first place
*/

void	pwd(void)
{
	char	*a;

	a = getcwd(NULL, 0);
	if (a == NULL)
	{
		ft_dprintf(2, "Error: GETCWD returned NULL\n");
		g_ms->prompt->last_exit_code = 1;
		return ;
	}
	if (a)
	{
		ft_printf("%s\n", a);
		free(a);
	}
}
