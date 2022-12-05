/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 15:40:18 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/19 19:37:03 by rverscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		size;
	int		counter;
	char	*dup;

	size = 0;
	counter = 0;
	size = ft_strlen(s1);
	dup = ft_calloc(sizeof(char), size + 1);
	if (dup == NULL)
		return (NULL);
	while (counter < size)
	{
		dup[counter] = s1[counter];
		counter++;
	}
	dup[counter] = '\0';
	return (dup);
}
