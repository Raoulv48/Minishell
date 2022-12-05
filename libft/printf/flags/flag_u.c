/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_u.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 13:46:15 by jlensing      #+#    #+#                 */
/*   Updated: 2021/02/24 13:06:53 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/utils.h"

char	*flag_u(unsigned int value)
{
	char	*str;

	str = ft_itoa_util_unsigned_util(value);
	return (str);
}
