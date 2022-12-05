/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 13:30:26 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>
#include <libft.h>

int	main(int argv, char **argc)
{
	int	i;

	g_ms = malloc(sizeof(t_ms));
	g_ms->argv = argv;
	g_ms->argc = argc;
	if (ft_strcontains(argc[0], "/"))
	{
		i = ft_strlen(argc[0]);
		while (argc[0][i] != '/')
			i--;
		g_ms->prog_name = ft_substr(argc[0], i + 1, ft_strlen(argc[0]));
	}
	else
		g_ms->prog_name = argc[0];
	init_prompt();
}
