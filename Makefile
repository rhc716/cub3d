all: 
	make -C ./lib/libft
	make -C ./lib/minilibx-linux
	gcc -Wall -Wextra -Werror main.c parse.c error.c free.c valid.c init.c \
	-g -L./lib/minilibx-linux -lmlx -L./lib/libft -lft -lm -lXext -lX11
	./a.out ./map/map.cub