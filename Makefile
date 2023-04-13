# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 21:07:24 by cmenke            #+#    #+#              #
#    Updated: 2023/04/13 15:36:43 by cmenke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

SRCDIR := mandatory

SRCS := $(addprefix ${SRCDIR}/,main.c \
							list_functions.c)


OBJS := ${SRCS:.c=.o}

HEADER := ${SRCDIR}/so_long.h

LIBFTDIR := libft

LIBFT := libft.a

# INCLUDE := -L${LIBFTDIR} -l:${LIBFT}
INCLUDE := ${LIBFTDIR}/${LIBFT}

# CFLAGS := -Wall -Werror -Wextra

CC := cc

RM := rm -f

all: library ${NAME}

library:
	make -C ${LIBFTDIR}

${NAME}: ${OBJS} ${LIBFTDIR}/${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${INCLUDE} -o ${NAME}


${OBJS}: ${HEADER}

clean:
	${RM} ${OBJS}
	make clean -C ${LIBFTDIR}

fclean: clean
	${RM} ${NAME}
	make fclean -C ${LIBFTDIR}

re: fclean all

.PHONY: all clean fclean re library