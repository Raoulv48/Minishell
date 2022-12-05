/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   populate_list4.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 14:16:33 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 14:16:33 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>

static int	set_count(int j, char *dummy)
{
	j++;
	while (ft_isalnum(dummy[j]) || dummy[j] == '?' || dummy[j] == '_')
		j++;
	if (dummy[j] != '\0')
		if (!ft_isalnum(dummy[j]) || dummy[j] != '?' || dummy[j] == '_')
			j--;
	return (j);
}

static char	*set_newstr(int count, char *newstr2, char *newstr)
{
	char	*temp;

	newstr2[count] = '\0';
	newstr2 = replace_questiondollar(newstr2);
	newstr2 = replace_envvar(newstr2);
	temp = ft_strdup(newstr2);
	free(newstr2);
	newstr2 = NULL;
	newstr2 = ft_strjoin(newstr, temp);
	free(temp);
	temp = NULL;
	return (newstr2);
}

char	*add_rest_value(char *dummy, char *newstr, int j, int i)
{
	char	*newstr2;
	char	*temp;
	int		count;

	count = 0;
	newstr[i] = '\0';
	i = j;
	j = set_count(j, dummy);
	newstr2 = ft_calloc(j - i, sizeof(char));
	while (i <= j)
	{
		newstr2[count] = dummy[i];
		i++;
		count++;
	}
	newstr2 = set_newstr(count, newstr2, newstr);
	j = do_check(newstr2, j, dummy);
	if (ft_strlen(newstr2) > 0)
		temp = ft_calloc(ft_strlen(newstr2) + (j - i), sizeof(char));
	else
		temp = ft_strdup("");
	ft_strlcpy(temp, newstr2, ft_strlen(newstr2) + 1);
	free(newstr2);
	return (temp);
}

static	char	*set_red(char *red, char c1, char c2)
{
	if (c1 == '>' && c2 != '>')
		red = ft_strdup(">");
	if (c1 == '<' && c2 != '>')
		red = ft_strdup("<");
	if (c1 == '>' && c2 == '>')
		red = ft_strdup(">>");
	return (red);
}

char	*add_redir(char *dummy, char *newstr, int j, int i)
{
	t_list	*newlist;
	char	*newstr2;
	char	*red;

	newstr[i] = '\0';
	red = NULL;
	if (newstr != NULL && !ft_strequals(newstr, ""))
	{
		newlist = ft_lstnew(ft_strdup(newstr));
		ft_lstadd_back(&g_ms->prompt->argslist, newlist);
	}
	if (newstr != NULL)
		free(newstr);
	red = set_red(red, dummy[j], dummy[j + 1]);
	while (dummy[j] == '>' || dummy[j] == '<')
		j++;
	i = ft_strlen(dummy) - j + 1;
	newstr2 = ft_substr(dummy, j, ft_strlen(dummy));
	newlist = ft_lstnew(ft_strdup(red));
	ft_lstadd_back(&g_ms->prompt->argslist, newlist);
	free(red);
	free(dummy);
	dummy = NULL;
	red = NULL;
	return (newstr2);
}
