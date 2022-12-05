/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 16:45:46 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 16:03:23 by rverscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <minishell.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_presplits
{
	int			argv;
	char		**argc;
	int			pipe_size;
	char		**split_pipe;
}				t_presplits;

typedef struct s_path
{
	char		**res;
	int			size;
}				t_path;

typedef struct s_execstruct
{
	DIR				*dir;
	struct dirent	*file;
	char			*a;
	char			*res;
	t_path			path;
	int				flag;
	char			*trimmedstr;
	int				i;
}				t_execstruct;

void			init_prompt(void);
void			init_prompt_loop(_Bool *flag_arrow1, _Bool *flag_arrow2,
					void (*enableRaw)());
void			init_history(void);
void			init_prompt_2(void);
void			init_prompt_3(void);
void			set_env(void);
void			set_shlvl(char *env);
void			prompt_loop(t_presplits **arr, char **splits, int ret, int j);
void			clean_calc_values(void);
int				free_prompt_loop_1(int i, int j, t_presplits **arr);
void			free_prompt_loop_2(int i, t_presplits **arr, char **splits);
void			fill_prompt(int i, int j, t_presplits **arr);
void			pipe_loop(t_presplits **arr, int i, int j);
t_list			*populate_list(t_list *newlist);
void			set_check(const char *s, int i);
char			*add_rest_value(char *dummy, char *newstr, int j, int i);
char			*add_redir(char *dummy, char *newstr, int j, int i);
char			*add_char_to_string(char *dummy, char *newstr);
int				do_check(char *newstr2, int j, char *dummy);
char			*set_to_string(char *dummy);
int				to_join(char *dummy);
char			*join_quote(char *dummy);
char			*restart_to_string(char *newstr, char *dummy, int set);
void			reset_list_values(char *dummy);
void			populate_commands(void);
int				is_exec(void);
void			free_exec(void);
char			**ft_split_2(char *s, int c);
char			**ft_split_sc(char *s, int c);
int				ft_strequals(const char *str1, const char *str2);
int				is_existing_exec(void);
void			resume_output(void);
void			redirect_new(char *path);
void			redirect_append(char *path);
void			redirect_into(char *path);
void			redirect_output_to_pipe(void);
void			redirect_pipe_to_input(void);
void			resume_output2(void);
char			*replace_questiondollar(char *str);
char			*replace_envvar(char *str);
void			siginthandler(int sig);
void			sigquithandler(int sig);
void			sigsegvhandler(int sig);
void			new_line(_Bool *flag_arrow1, _Bool *flag_arrow2);
int				handler(const char *s, int c, int i);
void			handle_input(_Bool *flag_arrow1, _Bool *flag_arrow2,
					void (*clear), void (*add_history)(_Bool));
void			handle_command(void);
void			check_redirection(void);
int				check_exit(void);
void			free_content(void *arg);
_Bool			check_pipes_only(void);
_Bool			check_semicolumn_only(void);
_Bool			check_empty(void);
_Bool			check_return(char c);
void			reset_values_prompt(void (*disableRaw)(),
					void (*add_history)(_Bool));
void			disableRaw(void);
void			enableRaw(void);
void			check_exit_2(char c);
char			*getstr(char *str);
void			free_exec(void);
char			**return_env(void);
int				get_list_size(t_list *list);
char			**return_args(void);
void			execute_cmd(void);
void			get_prompt_loop_data(int i, int j,
					t_presplits **arr, char **splits);
t_presplits		**get_prompt_loop_data2(t_presplits **arr,
					int i, char **splits);
int				get_prompt_loop_data3(_Bool flag);

#endif
