NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c parse.c error.c free.c valid.c init.c ray_caster.c ray_main.c draw_player_and_ray.c \
		load_texture.c sprite.c save_bmp.c draw_map_line.c draw_background.c deal_key.c

PATHLIBFT = ./lib/libft
PATHMLXLIB = ./lib/minilibx-linux
LIBOPTION = -L$(PATHMLXLIB) -lmlx -lm -lXext -lX11 -L$(PATHLIBFT) -lft

OBJS = $(SRCS:.c=.o)

.c.o: 
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
		make all -C $(PATHLIBFT)
		make all -C $(PATHMLXLIB)
		$(CC) $(CFLAGS) -o $@ $^ $(LIBOPTION)

all: $(NAME)

clean: 
	rm -f $(OBJS)
	make clean -C $(PATHLIBFT)
	make clean -C $(PATHMLXLIB)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(PATHLIBFT)
	make clean -C $(PATHMLXLIB)

re: fclean all

.PHONY: all clean fclean re
