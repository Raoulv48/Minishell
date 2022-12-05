/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_sc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 01:36:07 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/19 14:13:56 by rverscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <limits.h>

static int	get_flag(int flag)
{
	if (flag == 0)
		flag = 1;
	else if (flag == 1)
		flag = 0;
	return (flag);
}

static void	set_index(char *s, int c, int *indexes)
{
	int		i;
	size_t	count;
	char	*quote;
	int		flag;
	int		flag1;

	flag = 0;
	flag1 = 0;
	quote = "'";
	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
			flag = get_flag(flag);
		else if (s[i] == quote[0])
			flag1 = get_flag(flag1);
		if (s[i] == c && s[i + 1] != '\0' && flag == 0 && flag1 == 0)
		{
			indexes[count] = i;
			count++;
		}
		i++;
	}
}

static int	calc(char *s, int c)
{
	int		i;
	size_t	count;
	int		flag;
	int		flag1;
	char	*quote;

	count = 0;
	i = 0;
	flag = 0;
	flag1 = 0;
	quote = "'";
	while (s[i] != '\0')
	{
		if (s[i] == '"')
			flag = get_flag(flag);
		else if (s[i] == quote[0])
			flag1 = get_flag(flag1);
		if (s[i] == c && s[i + 1] != '\0' && flag == 0 && flag1 == 0)
		{
			count++;
		}
		i++;
	}
	return (count + 1);
}
/*
** see test_split.c
** this does take into account char between '' and "" and does not splti these
*/

char	**ft_split_sc(char *s, int c)
{
	int		*indexes;
	int		i;
	int		size;
	char	**ret;

	size = calc(s, c);
	indexes = malloc(sizeof(int *) * size);
	i = 0;
	set_index(s, c, indexes);
	ret = malloc(sizeof(char *) * size);
	ft_bzero(ret, sizeof(char *) * size);
	if (indexes[0] <= 0)
		ret[0] = ft_substr(s, 0, (size_t)UINT_MAX);
	else
		ret[0] = ft_substr(s, 0, (size_t)indexes[0]);
	i = 0;
	while (i + 1 < size)
	{
		ret[i + 1] = ft_substr(s, indexes[i] + 1,
				(size_t)((indexes[i + 1] - indexes[i]) - 1));
		i++;
	}
	free(indexes);
	return (ret);
}
