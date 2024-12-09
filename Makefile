NAME=fdf

CC = gcc

SRC = main.c gnl.c gnl1.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -Ift $(LIBFT_INC) -O3 -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	git add .; git commit -m "auto"; git push
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -Ift -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

all: $(NAME)