/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envvar.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 01:38:14 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <libft.h>
#include <stdlib.h>

static char	*get_ret(char *str2, int i)
{
	char	*ret;

	while (str2[i] != '=')
		i++;
	ret = ft_substr(str2, i + 1, ft_strlen(str2));
	free (str2);
	return (ret);
}

static char	*getenvvar(char *str)
{
	t_list	*cur;
	int		i;
	char	*str2;
	char	*getstrr;

	i = 0;
	cur = g_ms->prompt->envi;
	while (cur != NULL)
	{
		str2 = ft_strdup(cur->content);
		getstrr = getstr(cur->content);
		if (ft_strncmp(getstrr, str, ft_strlen(str)) == 0
			&& ft_strlen(str) == ft_strlen(getstrr))
		{
			if (getstrr != NULL)
				free(getstrr);
			return (get_ret(str2, i));
		}
		free(str2);
		cur = cur->next;
		if (getstrr != NULL)
			free(getstrr);
	}
	return (ft_strdup(""));
}

static int	get_second_pos(char *str, int i, int j)
{
	while (str[i + j] != ' '
		&& str[i + j] != '\0'
		&& str[i + j] != g_ms->prompt->db_quote
		&& str[i + j] != g_ms->prompt->quote[0]
		&& str[i + j] != '$'
		&& str[i + j] != '?')
		j++;
	return (j);
}

static char	*replace_envvar2(char *str, int i, int j)
{
	char	*temp;
	char	*temp2;
	char	*str2;
	char	*envvar;

	if (str[i] == '$')
	{
		j = get_second_pos(str, i, j);
		str2 = ft_substr(str, i + 1, j - 1);
		temp = ft_substr(str, 0, i);
		temp2 = ft_substr(str, i + j, ft_strlen(str));
		envvar = getenvvar(str2);
		temp = ft_strjoin(temp, envvar);
		if (envvar != NULL)
			free(envvar);
		free(str2);
		temp = ft_strjoin(temp, temp2);
		if (temp2 != NULL)
			free(temp2);
		free(str);
		str = ft_strdup(temp);
		if (temp != NULL)
			free(temp);
	}
	return (str);
}

char	*replace_envvar(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (ft_strcontains(str, "$"))
	{
		while (str[i] != '\0')
		{
			str = replace_envvar2(str, i, j);
			i++;
		}
		i = 0;
	}
	return (str);
}
