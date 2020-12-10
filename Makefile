all: 
	make -C ./lib/libft
	gcc -Wall -Wextra -Werror main.c parse.c error.c free.c valid.c \
	-g -L./lib/minilibx-linux -lmlx_Linux -L./lib/libft -lft -lm -lXext -lX11
	./a.out ./map/map.cub