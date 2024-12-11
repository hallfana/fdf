NAME=fdf
CC = gcc
SRC = \
	./src/main.c \
	./src/get_next_line/get_next_line.c \
	./src/get_next_line/get_next_line_utils.c \
	./src/init/mlx_init.c \
	./src/init/tab_init.c \
	./src/init/tab_populate.c \
	./src/perspective/calculate_draw.c \
	./src/draw/draw.c \
	./src/draw/mlx_draw.c \
	./src/hook/keyboard.c \
	./src/utils/atoi_base.c \
	

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -I./includes -Imlx_linux -Ift -O3 -g -c $< -o $@

$(NAME): $(OBJ) libft
	git add .; git commit -m "auto"; git push
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -Ift -lXext -lX11 -lm -lz -g -L./libs -lft -g -fsanitize=address -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make -C ./libs fclean

re: fclean all

all: $(NAME)

libft:
	make -C ./libs

PHONY: all clean fclean re