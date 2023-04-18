# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 21:07:24 by cmenke            #+#    #+#              #
#    Updated: 2023/04/19 00:56:24 by cmenke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# := sets the value only once

NAME := so_long

SRCDIR := mandatory

SRCS := $(addprefix ${SRCDIR}/,main.c \
							list_functions.c \
							check_map_format.c \
							check_map_path.c \
							close_free.c \
							read_map.c \
							calculate_pov.c \
							events_and_key_press.c \
							put_map_on_screen.c \
							messages.c)


OBJS := ${SRCS:.c=.o}

HEADER := ${SRCDIR}/so_long.h

LIBFTDIR := libft

LIBFT := libft.a

MLXDIR := mlx

MLXLIB := libmlx.a

# INCLUDE := -L${LIBFTDIR} -l:${LIBFT}
INCLUDE := ${LIBFTDIR}/${LIBFT} ${MLXDIR}/${MLXLIB} -framework OpenGL -framework AppKit

CFLAGS := -Wall -Werror -Wextra

CC := cc

RM := rm -f

all: library ${NAME}

library:
	make -C ${LIBFTDIR}
	make -C ${MLXDIR}

${NAME}: ${OBJS} ${LIBFTDIR}/${LIBFT} ${MLXDIR}/${MLXLIB}
	${CC} ${CFLAGS} ${OBJS} ${INCLUDE} -o ${NAME}


${OBJS}: ${HEADER}

clean:
	${RM} ${OBJS}
	make clean -C ${LIBFTDIR}
	make clean -C ${MLXDIR}

fclean: clean
	${RM} ${NAME}
	make fclean -C ${LIBFTDIR}
	make clean -C ${MLXDIR}

re: fclean all

.PHONY: all clean fclean re library