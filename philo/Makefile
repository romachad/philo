NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS_FILES = main ft_atoi init threads loops eat_loop one_philo
SRCS_DIR = srcs/
HEADERS_FILES = philo
HEADERS_DIR = headers/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_FILES)))
HEADERS = $(addprefix $(HEADERS_DIR), $(addsuffix .h, $(HEADERS_FILES)))
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))


all:
	make $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean:
	rm -rf $(OBJS_DIR)
	rm -rf $(NAME)

re:
	fclean all

.PHONY: all clean fclean re
