/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   terms_3.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 14:16:43 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 16:02:49 by rverscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>

void	new_line(_Bool *flag_arrow1, _Bool *flag_arrow2)
{
	int	i;

	i = 0;
	while (g_ms->prompt->line[i] != '\n')
		i++;
	g_ms->prompt->line = ft_substr(g_ms->prompt->line, 0, i);
	*flag_arrow1 = FALSE;
	*flag_arrow2 = FALSE;
}

int	handler(const char *s, int c, int i)
{
	while (s[i] != '\0')
	{
		set_check(s, i);
		if (s[i] == c && g_ms->prompt->q_check != 1)
		{
			i = i + 1;
			while (s[i] != '\0')
			{
				if (s[i] != c && s[i] != ' ')
					break ;
				if (s[i] == c)
				{
					clean_calc_values();
					return (-1);
				}
				i = i + 1;
			}
		}
		i = i + 1;
	}
	clean_calc_values();
	return (0);
}
