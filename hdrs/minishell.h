/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jlensing <jlensing@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 16:44:00 by jlensing      #+#    #+#                 */
/*   Updated: 2021/05/20 14:12:07 by jlensing      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <sys/types.h>
# include <limits.h>
# include <termios.h>

# define ARROW_UP 65
# define ARROW_DOWN 66
# define BACKSPACE 127
# define RETURN 10
# define CMD_AMOUNT 10

typedef struct s_pipe
{
	int			pipe[2];
}				t_pipes;

typedef struct s_prompt
{
	char				*line_start;
	char				*line;
	int					line_flag;
	char				**args;
	int					sc_size;
	int					argv;
	t_list				*argslist;
	int					i_list;
	struct s_commands	*commands;
	pid_t				pid;
	char				*quote;
	int					db_quote;
	int					red_fd;
	int					red_fd2;
	int					last_exit_code;
	t_list				*envi;
	t_list				*envi_copy;
	int					stdinfd;
	int					stdoutfd;
	int					bslashflag;
	struct s_exec		*exec;
	int					q_check;
	int					q_type;
	int					i;
	int					j;
	int					has_pipe;
	t_pipes				*pipes;
	int					pipe_size;
	int					pipe_count;
	int					q_bool_envar;
	int					one_space;
	char				c;
	struct termios		orig_termios;
}						t_prompt;

typedef struct s_history
{
	char	**history;
	int		counter;
	int		len;
	int		cur_pos;
}			t_history;

typedef struct s_ms
{
	t_prompt		*prompt;
	int				argv;
	char			**argc;
	char			*prog_name;
	t_history		*history;
	struct s_term	*term;
}					t_ms;

typedef struct s_commands
{
	char		*name;
	void		(*f)(void);
}				t_commands;

typedef struct s_exec
{
	char		**args;
	char		**env;
	int			flag;
}				t_exec;

typedef struct s_term
{
	int			width;
	int			height;
	int			cur_line;
}				t_term;

t_ms	*g_ms;
#endif
