/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strequals.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/28 16:55:28 by jlensing      #+#    #+#                 */
/*   Updated: 2021/02/28 16:55:35 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strequals(const char *str1, const char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0
		&& ft_strlen(str1) == ft_strlen(str2))
		return (1);
	return (0);
}
