/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/18 15:30:07 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/12 00:15:08 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <limits.h>
#include <prompt.h>

/*
** Finds and sets the indexes of char c in the array
*/

static void	set_index(char *s, int c, int *indexes)
{
	int		i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		set_check(s, i);
		if (s[i] == c && s[i + 1] != '\0' && g_ms->prompt->q_check == 0)
		{
			indexes[count] = i;
			count++;
		}
		i++;
	}
}

/*
** This simply calculates the total amount of char c present in the given string
** plus 1
*/

static int	calc(char *s, int c)
{
	int		i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		set_check(s, i);
		if (s[i] == c && s[i + 1] != '\0' && g_ms->prompt->q_check == 0)
		{
			count++;
		}
		i++;
	}
	return (count + 1);
}

/*
** Split an an given string by character c into a 2 Dimensional array
** by calling substring with the previous index of char c (or 0)
** and the next index (or max size if the character doesn't exist in the string)
** this way the char c will stay inside the final array
*/

char	**ft_split_2(char *s, int c)
{
	int		*indexes;
	int		i;
	int		size;
	char	**ret;

	size = calc(s, c);
	g_ms->prompt->q_type = 0;
	g_ms->prompt->q_check = 0;
	indexes = malloc(sizeof(int *) * size);
	i = 0;
	set_index(s, c, indexes);
	ret = malloc(sizeof(char *) * size);
	if (indexes[0] <= 0)
		ret[0] = ft_substr(s, 0, (size_t)UINT_MAX);
	else
		ret[0] = ft_substr(s, 0, (size_t)indexes[0]);
	i = 0;
	while (i + 1 < size)
	{
		ret[i + 1] = ft_substr(s, indexes[i] + 1, (size_t)((indexes[i + 1]
						- indexes[i])));
		i++;
	}
	free(indexes);
	return (ret);
}
