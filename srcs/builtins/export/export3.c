/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 20:58:04 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 20:58:04 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include <prompt.h>

char	*getstr(char *str)
{
	int		i;
	char	*ret;

	ret = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			ret = ft_substr(str, 0, i);
			break ;
		}
		i++;
	}
	return (ret);
}
