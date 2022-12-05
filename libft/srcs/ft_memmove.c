/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 18:56:17 by jlensing      #+#    #+#                 */
/*   Updated: 2021/02/24 14:12:10 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static char	*copy(char *tdst, char *tsrc, int counter, size_t len)
{
	while (counter < (int)len)
	{
		tdst[counter] = tsrc[counter];
		counter++;
	}
	return (tdst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*tdst;
	char	*tsrc;
	int		counter;

	tdst = (char *)dst;
	tsrc = (char *)src;
	counter = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst < src)
		tdst = copy(tdst, tsrc, counter, len);
	else
	{
		counter = (int)len;
		while (counter != 0)
		{
			tdst[counter - 1] = tsrc[counter - 1];
			counter--;
		}
	}
	return (tdst);
}
