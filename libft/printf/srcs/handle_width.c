/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_width.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 18:26:00 by jlensing      #+#    #+#                 */
/*   Updated: 2021/02/24 13:40:01 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/ft_printf.h"
#include "../hdrs/utils.h"

int	handle_width(struct s_info info, char *str, int i)
{
	if (ft_strlen_util(str) - info.toprint < 0)
	{
		while (i < (info.width - info.toprint))
		{
			info = ft_putchar_fd_util(info.fd, ' ', info);
			i++;
		}
	}
	else
	{
		while (i < ((info.width - ft_strlen_util(str))
				+ (ft_strlen_util(str) - info.toprint)))
		{
			info = ft_putchar_fd_util(info.fd, ' ', info);
			i++;
		}
		while (info.width == info.toprint
			&& i < info.width - ft_strlen_util(str))
		{
			info = ft_putchar_fd_util(info.fd, ' ', info);
			i++;
		}
	}
	return (i);
}
