NAME = minishell

SRC = main.c

PROMPT_SRC = input/init.c input/input.c input/input_2.c input/input_3.c input/populate_list.c \
			 input/populate_list2.c input/populate_list3.c input/populate_list4.c \
			 commands/populate_commands.c executable/executable.c redirections/redirections.c \
			 redirections/redirections_2.c dollarquestion/dollarquestion.c signals/signals.c \
			 envvar/envvar.c input/terms_1.c input/init_2.c input/terms_2.c input/terms_3.c \
			 input/input_4.c input/terms_4.c executable/executable_2.c input/input_5.c \
			 input/input_6.c

BUILTINS_SRC = exit/exit.c cd/cd.c pwd/pwd.c echo/echo.c env/env.c export/export.c \
			   export/export2.c unset/unset.c unset/unset_2.c clean/clean.c help/help.c \
			   help/mad.c export/export3.c

UTIL_SRC = calc_argv.c split_2.c split_sc.c ft_strequals.c

PROMPT_MAP = srcs/prompt/

BUILTINS_MAP = srcs/builtins/

UTIL_MAP = srcs/util/

PROMPT_SRCS = $(addprefix $(PROMPT_MAP), $(PROMPT_SRC))

BUILTINS_SRCS = $(addprefix $(BUILTINS_MAP), $(BUILTINS_SRC))

UTIL_SRCS = $(addprefix $(UTIL_MAP), $(UTIL_SRC))

SRCS = srcs/main.c $(PROMPT_SRCS) $(BUILTINS_SRCS) $(UTIL_SRCS)

LIBS = libft/libft.a

HDRS = -I hdrs/ -I libft/hdrs

OBJS := $(SRCS:.c=.o)

all: libft $(NAME)

libft:
	@$(MAKE) -C libft/ all
	
$(NAME): $(OBJS)
	clang -o $@ $(OBJS) $(LIBS) $(HDRS) -ltermcap -Wall -Werror -Wextra

%.o: %.c
	clang -o $@ -c $^ $(HDRS) -Wall -Werror -Wextra

clean:
	@$(MAKE) -C libft/ clean
	@rm  -f $(OBJS)

fclean: clean
	@$(MAKE) -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all libft clean fclean re