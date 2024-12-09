NAME=fdf

CC = gcc

SRC = main.c gnl.c gnl1.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -Ilibft -O3 -c $< -o $@

$(NAME): $(OBJ)
	git add .; git commit -m "auto"; git push
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -Ilibft -lXext -lX11 -lm -lz -o $(NAME)	
