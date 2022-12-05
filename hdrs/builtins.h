/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 17:02:08 by jlensing      #+#    #+#                 */
/*   Updated: 2021/02/28 18:05:02 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <minishell.h>

void	exit_ms(void);
void	cd(void);
void	pwd(void);
void	echo(void);
void	unset(void);
void	env(void);
void	export_function(void);
void	clean(void);
void	help_cmd(void);
void	mad(void);
int		calc_argv(const char *s, int c);
int		calc_argv_sc(const char *s, int c);

#endif
