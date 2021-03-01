NAME = libftprintf.a

SRCS = ft_printf.c \
		parse_type_pct.c \
		parse_type_c.c \
		parse_type_s.c \
		parse_type_p.c \
		parse_type_di.c \
		parse_type_ux.c \
		libft_utils.c \
		other_utils.c \
		parse_tag.c

OBJS = $(SRCS:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror

$(NAME) : $(OBJS)
	ar rc $@ $^

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
