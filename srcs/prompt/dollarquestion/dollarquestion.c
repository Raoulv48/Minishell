/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollarquestion.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 22:32:58 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <libft.h>
#include <stdlib.h>

static char	*local_free(char *str, char *temp, char *temp2)
{
	temp = ft_strjoin(temp, temp2);
	free(str);
	free(temp2);
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

char	*replace_questiondollar(char *str)
{
	char	*temp;
	char	*temp2;
	char	*itoa;
	int		i;

	i = 0;
	if (g_ms->prompt->pipe_size > 1)
		g_ms->prompt->last_exit_code = 0;
	while (ft_strcontains(str, "$?") && str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			temp = ft_substr(str, 0, i);
			temp2 = ft_substr(str, i + 2, ft_strlen(str));
			itoa = ft_itoa(g_ms->prompt->last_exit_code);
			temp = ft_strjoin(temp, itoa);
			free(itoa);
			str = local_free(str, temp, temp2);
			i = 0;
		}
		i++;
	}
	return (str);
}
