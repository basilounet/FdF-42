SRC =	fdf.c \
		draw_lines.c \
		errors.c \
		map_analyser.c \
		struct_init.c \
		unleak.c
OBJS = $(SRC:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = $(LIBS) #-fsanitize=address
MLX_INCLUDE_FLAGS = -I/usr/include -Imlx_linux -O3 -c
MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
NAME = fdf
LIBFT = libft/libft.a
MLX42 = MLX42/build/libmlx42.a
LIBMLX	:= ./MLX42
LIBS	:= -L$(LIBMLX)/build -lmlx42 -ldl -lglfw -pthread -lm -Llibft -lft

all : libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build --no-print-directory -j4

$(NAME) : $(OBJS) $(LIBFT)
		$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LDFLAGS)

%.o : %.c
	@$(CC) $(CFLAGS) $(MLX_INCLUDE_FLAGS) -c $< -o $@

$(LIBFT) :
	@$(MAKE) -C libft --no-print-directory -j4

clean :
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@$(MAKE) -C libft clean --no-print-directory

fclean : clean
	@rm -rf $(NAME)
	@$(MAKE) -C libft fclean --no-print-directory
	@echo "Files cleaned"

first : 
	@git clone https://github.com/codam-coding-college/MLX42.git

cleanall : fclean
	@rm -rf MLX42

re : fclean all

.PHONY : all clean fclean re libmlx first cleanall