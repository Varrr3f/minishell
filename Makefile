SRCS	=	minishell.c envp_utils.c parser.c signals.c parse_help.c\
			parse_help1.c exe_cmds.c pipes.c builtins.c\
			exe_cmds1.c clear.c builtins1.c exit_ms.c unset_ms.c export_ms.c\

OBJS	=	$(SRCS:.c=.o)

HEADS	=	./includes

NAME	=	minishell

LNAME	=	libft/libft.a

RL_LIB	=	readline/libreadline.a

HS_LIB	=	readline/libhistory.a

GCC		=	gcc

FLAGS	=	-Wall -Werror -Wextra #-g -fsanitize=address

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