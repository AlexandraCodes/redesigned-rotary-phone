#all, clean, fclean, re, bonus

# NAME = my_printf
NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INC_PATH = printf.h

SRC_NAME = ft_printf.c

OBJ_NAME = $(SRC_NAME:.c=.o)

# %.o: %.c $(INC_PATH)
# 	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJ_NAME)
		ar -vrc ${NAME} ${OBJ_NAME}

%.o: %.c $(INC_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJ_NAME)
# 	$(CC) $(CFLAGS) -o $@ $^

all: $(NAME)

bonus: ${NAME}

clean:
	@rm -rf $(OBJ_NAME)

fclean: clean
		@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

#%.o: %.c $(DEPS)
#	$(CC) -c -o $@ $< $(CFLAGS)

#hellomake: printf.o
#	$(CC) -o hellomake printf.o
