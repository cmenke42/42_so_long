# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 21:07:24 by cmenke            #+#    #+#              #
#    Updated: 2023/04/19 02:06:19 by cmenke           ###   ########.fr        #
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

BSCRDIR := bonus

BSRCS := $(addprefix ${BSCRDIR}/,main_bonus.c \
							list_functions_bonus.c \
							check_map_format_bonus.c \
							check_map_path_bonus.c \
							close_free_bonus.c \
							read_map_bonus.c \
							calculate_pov_bonus.c \
							events_and_key_press_bonus.c \
							put_map_on_screen_bonus.c \
							messages_bonus.c)


OBJS := ${SRCS:.c=.o}

BOBJS := ${BSRCS:.c=.o}

HEADER := ${SRCDIR}/so_long.h

BHEADER := ${BSCRDIR}/so_long_bonus.h

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
	${RM} ${BOBJS}
	make clean -C ${LIBFTDIR}
	make clean -C ${MLXDIR}

fclean: clean
	${RM} ${NAME}
	make fclean -C ${LIBFTDIR}
	make clean -C ${MLXDIR}

bonus: library ${BSCRDIR}/${NAME}

${BSCRDIR}/${NAME}: ${BOBJS} ${LIBFTDIR}/${LIBFT} ${MLXDIR}/${MLXLIB}
	${CC} ${CFLAGS} ${BOBJS} ${INCLUDE} -o ${NAME}

${BOBJS}: ${BHEADER}

re: fclean all

.PHONY: all clean fclean re library bonus

.NOTPARALLEL: