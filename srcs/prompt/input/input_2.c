/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/28 16:47:33 by jlensing      #+#    #+#                 */
/*   Updated: 2021/03/02 15:54:19 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>
#include <libft.h>

void	right_one(t_list *current, char *temp)
{
	if (ft_strequals(current->next->content, "")
		&& current->next->next != NULL)
		redirect_new(current->next->next->content);
	else
		redirect_new(current->next->content);
	free(temp);
}

void	right_two(t_list *current, char *temp)
{
	if (ft_strequals(current->next->content, "")
		&& current->next->next != NULL)
		redirect_append(current->next->next->content);
	else
		redirect_append(current->next->content);
	free(temp);
}

void	left_one(t_list *current, char*temp)
{
	if (ft_strequals(current->next->content, "")
		&& current->next->next != NULL)
		redirect_into(current->next->next->content);
	else
		redirect_into(current->next->content);
	free(temp);
}
