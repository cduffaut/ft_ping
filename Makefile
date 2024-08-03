SRCS	= \
		program/ft_ping.c \
		program/parsing.c \
		program/request.c \
		program/ping_stats.c \
		program/linked_list.c \
		program/utils.c

OBJS	= $(SRCS:.c=.o)

GCC		= gcc -Wall -Wextra -Werror

NAME	= ft_ping

all: $(NAME)
	make -C libft 

$(NAME): $(OBJS)
	$(GCC) -o $(NAME) $(OBJS) -Llibft -lft

.c.o:
	$(GCC) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
	make re -C libft

.PHONY: re fclean clean all 