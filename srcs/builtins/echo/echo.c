/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/18 15:27:19 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <libft.h>
#include <stdlib.h>

/*
** Start at the first argument and print out each of the arguments
** ends with a new line at the end
*/

static void	without_n(t_list *cur)
{
	t_list	*curr;

	curr = cur;
	while (curr != NULL)
	{
		ft_printf("%s", curr->content);
		if (curr->next != NULL)
			ft_printf(" ");
		curr = curr->next;
	}
	ft_printf("\n");
}

/*
** Same as above but without printing a new line
** also starts one argument later
*/

static void	with_n(t_list *cur)
{
	t_list	*curr;

	curr = cur;
	while (curr != NULL)
	{
		ft_printf("%s", curr->content);
		if (curr->next != NULL)
			ft_printf(" ");
		curr = curr->next;
	}
}

static int	check_arg_exists(void)
{
	if (g_ms->prompt->argslist->next == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	return (1);
}

/*
** Checks wether or not the first arguments after echo is -n
** if so it will call the with_n() function
** if not call the without_n() function
*/

static void	descision(int flag, t_list *cur)
{
	if (flag == 1)
		with_n(cur);
	else
		without_n(cur);
}

void	echo(void)
{
	char	*value;
	t_list	*cur;
	int		flag;

	if (!check_arg_exists())
		return ;
	cur = g_ms->prompt->argslist->next;
	flag = 0;
	value = NULL;
	while (cur != NULL)
	{
		value = ft_strdup(cur->content);
		if (value[0] != '-' || !ft_str_only_contains(value, "-n"))
			break ;
		else if (value[0] == '-' && ft_str_only_contains(value, "-n"))
			flag = 1;
		free(value);
		value = NULL;
		cur = cur->next;
	}
	descision(flag, cur);
	if (value != NULL)
		free(value);
}
