NAME = libft.a

HEADER = libft.h

LIST = ft_atoi.c    ft_bzero.c   ft_isalnum.c ft_isalpha.c\
	   ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c\
	   ft_memcmp.c   ft_memcpy.c ft_memmove.c ft_memset.c\
	   ft_strchr.c  ft_strlcat.c ft_strlcpy.c ft_strlen.c\
	   ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_toupper.c ft_tolower.c\
	   ft_itoa.c    ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	   ft_putstr_fd.c ft_split.c ft_striteri.c ft_strtrim.c\
	   ft_strjoin.c ft_strdup.c ft_substr.c ft_calloc.c ft_strmapi.c\
	   get_next_line.c get_next_line_utils.c

LIST_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
	   ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c

OBJS = $(patsubst %.c,%.o,$(LIST))

OBJS_BONUS = $(patsubst %.c,%.o,$(LIST_BONUS))

FLAGS = -Wall -Wextra -Werror

.PHONY : all clean fclean re bonus

all : $(NAME) $(HEADER)
 
$(NAME) : $(OBJS)
	ar rcs $(NAME) $?

%.o : %.c libft.h
	CC $(FLAGS) -c $< -o $@ -I ${HEADER}

bonus : $(OBJS_BONUS) 
	ar rcs $(NAME) $(OBJS_BONUS)

clean :
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean : clean
	@rm -f $(NAME) 

re : fclean all