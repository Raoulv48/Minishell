/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_c.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/20 19:16:23 by jlensing      #+#    #+#                 */
/*   Updated: 2021/02/24 13:06:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*flag_c(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 1);
	if (str == NULL)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
