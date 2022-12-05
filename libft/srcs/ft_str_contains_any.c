/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str_contains_any.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 18:44:58 by jlensing      #+#    #+#                 */
/*   Updated: 2021/02/24 14:14:40 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/libft.h"

static int	in_set(int c, char *set)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			flag = 1;
		i++;
	}
	return (flag);
}

int	ft_str_only_contains(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (in_set(str[i], set) == 0)
			return (0);
		i++;
	}
	return (1);
}
