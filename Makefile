SRCS	=	excve_pipes.c get_cmd_args.c builtins.c signal1.c clear_commands_array.c utils_funcs1.c\
			utils_funcs2.c get_command_information.c pipes_cmds.c get_total_commands_validate_line.c\
			here_doc.c minishell.c parser.c parse_path.c pipes.c num_of_cmds.c redirects.c\
			func_del_q.c del_redirs.c signal2.c wait_child_process.c\
			cd_utils.c cd_ms.c echo_ms.c env_ms.c exit_ms.c export_ms.c export_utils.c pwd_ms.c unset_ms.c\
			libft/ft_atoi.c    libft/ft_bzero.c   libft/ft_isalnum.c libft/ft_isalpha.c\
	   		libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_memchr.c\
	   		libft/ft_memcmp.c   libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c\
	   		libft/ft_strchr.c  libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c\
	   		libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_toupper.c libft/ft_tolower.c\
	   		libft/ft_itoa.c    libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c\
	   		libft/ft_putstr_fd.c libft/ft_split.c libft/ft_striteri.c libft/ft_strtrim.c\
	  		libft/ft_strdup.c libft/ft_substr.c libft/ft_calloc.c libft/ft_strmapi.c\
	   		libft/get_next_line.c libft/get_next_line_utils.c libft/ft_strjoin.c\

OBJS	=	$(SRCS:.c=.o)

HEADS	=	./includes

NAME	=	minishell

LNAME	=	libft/libft.a

RL_LIB	=	readline/libreadline.a

HS_LIB	=	readline/libhistory.a

GCC		=	gcc

FLAGS	=  -Wall -Werror -Wextra

RM		=	rm -f

%.o: %.c minishell.h
	$(GCC) $(FLAGS) -I$(HEADS) -c $< -o $@ 

$(NAME): $(OBJS) ./libft/libft.h
	$(MAKE) -C libft bonus
	$(GCC) $(FLAGS) $(OBJS) $(LNAME) $(RL_LIB) $(HS_LIB) -ltermcap -lreadline -o $(NAME)

all:	$(NAME)

clean:
		$(MAKE) -C libft clean
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(LNAME)
		$(RM) $(NAME)

re:		fclean all
