all: 
	make -C ./lib/libft
	make -C ./lib/minilibx-linux
	gcc -Wall -Wextra -Werror main.c parse.c error.c free.c valid.c init.c ray_caster.c ray_main.c \
	-g -L./lib/minilibx-linux -lmlx -lm -lXext -lX11 -L./lib/libft -lft
	./a.out ./map/map.cub