NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDE	= -Iinclude
SRC_DIR	= srcs
OBJ_DIR	= obj
SRCS = ft_atoi.c ft_isdigit.c init.c monitor.c parse.c \
	philo.c routine.c utils.c
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
