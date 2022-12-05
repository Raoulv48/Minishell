/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/20 14:15:55 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 14:15:55 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSET_H
# define UNSET_H

int		unset_initial_2(t_list *env, char *curc);
t_list	*unset_non_initial_2(t_list *env, char *curc);

#endif
