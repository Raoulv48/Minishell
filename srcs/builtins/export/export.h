/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 21:13:13 by jlensing      #+#    #+#                 */
/*   Updated: 2021/02/26 14:49:18 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

char	*getstr(char *str);
int		export_exists(char *str);
void	copy_list(void);
void	restore_list(void);

#endif
