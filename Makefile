# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/11 13:33:31 by Ektin Op Urims    #+#    #+#              #
#    Updated: 2023/09/22 14:36:08 by Ektin Op Urims   ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = fdf.c \
	finish_objects.c \
	data.c \
	point.c \
	vector_setting.c \
	vector_operations.c \
	events.c \
	events2.c \
	events3.c \
	draw_line.c \
	draw_line_aux.c \
	adjust_points_for_draw_line.c \
	adjust_points_for_draw_line_aux1.c \
	adjust_points_for_draw_line_aux2.c \
	ft_math.c \
	read_input_aux.c \
	read_input.c \
	isoplane_setting.c \
	isoplane_computing_part1.c \
	isoplane_computing_part2.c \
	isoplane_computing_part2b.c \
	isoplane_computing_part3.c \
	isoplane_change_params.c \
	set_maxminxy_proj.c \

HEADER = fdf.h

SRCDIR = srcs/
SRC_FILES = $(addprefix $(SRCDIR), $(SRC))
HEADER_FILE = $(addprefix srcs/, $(HEADER))
OBJ = $(SRC_FILES:.c=.o)

NAME = fdf

LIBFTDIR = libft/
NAMELIBFT = $(addprefix $(LIBFTDIR), libft.a)
SHORTNAMELIBFT = -lft
MINILIBXDIR = minilibx-linux/
NAMEMINILIBX = $(addprefix $(MINILIBXDIR), minilibx-linux.a)
SHORTNAMEMINILIBX = -lmlx -lXext -lX11

CC = gcc
CFLAGS += -Wall -Wextra -Wpedantic -Werror
LIBFLAGS += -lft -I$(LIBFTDIR) -L$(LIBFTDIR)
LIBFLAGS += -lmlx -lXext -lX11 -I$(MINILIBXDIR) -L$(MINILIBXDIR)
CFLAGS += $(LIBFLAGS)
CFLAGS += -lm
NORM = /bin/norminette

all: $(NAME)
	echo $(NAMELIBFT)

NORM:
	@if [ "$(wildcard $(NORM))" != "" ]; then \
		$(NORM) $(SRC_FILES) $(HEADER_FILE);\
	fi

$(NAME):	$(NAMELIBFT) $(NAMEMINILIBX) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)
	make NORM

%.o:	%.c
	echo "Salut"
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAMELIBFT):
	make -C $(LIBFTDIR)

$(NAMEMINILIBX):
	make -C $(MINILIBXDIR)

clean:
	make -C $(LIBFTDIR) clean
	make -C $(MINILIBXDIR) clean
	rm -f $(wildcard $(SRCDIR)*.o) $(wildcard $(SRCDIR)*.h.gch) $(wildcard $(SRCDIR).*.swp)

fclean:	clean
	make -C $(LIBFTDIR) fclean
	rm -f $(wildcard *.a) $(wildcard *.out) $(wildcard *.so) $(NAME)

re:
	make -C $(LIBFTDIR) fclean
	make fclean
	make -C $(MINILIBXDIR) re
	make
