# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jlensing <jlensing@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/28 12:23:24 by jlensing      #+#    #+#                  #
#    Updated: 2021/05/12 15:20:22 by jlensing      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_strlen.c ft_atoi.c ft_tolower.c ft_isalpha.c ft_isdigit.c ft_isalnum.c\
	ft_isascii.c ft_isprint.c ft_toupper.c ft_strncmp.c ft_memset.c ft_bzero.c\
	ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strchr.c\
	ft_strlcpy.c ft_strlcat.c ft_strrchr.c ft_strnstr.c ft_calloc.c ft_strdup.c\
	ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_strtrim.c\
	ft_itoa.c ft_strmapi.c ft_strjoin.c ft_substr.c ft_split.c ft_lstnew.c\
	ft_lstsize.c ft_lstadd_front.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
	ft_lstiter.c ft_lstmap.c ft_lstclear.c ft_contains.c ft_str_contains_any.c \
	ft_get_lst_content.c ft_del_lst_index.c

PRINTF_SRC = ft_printf.c flag_checker.c flag_handler.c in_set.c in_flag_set.c \
		handle_precision.c handle_width.c handle_negative.c \
		flag_handler_sub_1.c flag_handler_sub_2.c flag_handler_sub_3.c

PRINTF_SRC_MAP = printf/srcs/

PRINTF_UTIL_SRC = ft_putchar_fd.c ft_putstr_fd.c ft_tolower.c \
 			ft_convert_to_hex.c ft_strdup.c ft_strlen.c ft_toupper.c \
			ft_itoa.c ft_atoi.c ft_substr.c ft_strncmp.c ft_strlcat.c \
		 	ft_strlcpy.c ft_itoa_unsigned.c ft_strjoin.c

PRINTF_UTIL_MAP = printf/utils/

PRINTF_FLG = flag_c.c flag_p.c flag_s.c flag_di.c flag_u.c flag_x.c \
				flag_procent.c flag_width.c

PRINTF_FLG_MAP = printf/flags/

GNL_SRC = get_next_line_utils.c get_next_line.c get_next_line_2.c

GNL_MAP = get_next_line/

SRC_MAP = srcs/

GNL_SRCS = $(addprefix $(GNL_MAP), $(GNL_SRC))

PRINTF_SRCS = $(addprefix $(PRINTF_SRC_MAP), $(PRINTF_SRC))

PRINTF_UTILS = $(addprefix $(PRINTF_UTIL_MAP), $(PRINTF_UTIL_SRC))

PRINTF_FLGS = $(addprefix $(PRINTF_FLG_MAP), $(PRINTF_FLG))

SRCS = $(addprefix $(SRC_MAP), $(SRC))

OBJ := $(SRCS:.c=.o) $(PRINTF_SRCS:.c=.o) $(PRINTF_UTILS:.c=.o) \
		$(PRINTF_FLGS:.c=.o) $(GNL_SRCS:.c=.o)

HDR = -I hdrs 

FLAGS = -Wall -Werror -Wextra -fPIC

all: $(NAME) 

$(NAME): $(OBJ)
	@$(AR) rcs $@ $^
	@echo "Compiled libft!                                                      "

%.o: %.c
	@clang -o $@ -c $< $(FLAGS) 
	@bash -c "echo -ne 'libft: building object: $@                                               \r'"

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all


.PHONY: libft all clean fclean re