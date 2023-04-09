# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenke <cmenke@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 21:07:24 by cmenke            #+#    #+#              #
#    Updated: 2023/04/09 12:16:39 by cmenke           ###   ########.fr        #
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

INCLUDE := -l:${LIBFT} -L${LIBFTDIR}

# CFLAGS := -Wall -Werror -Wextra

CC := cc

RM := rm -f

all: library ${NAME}

library:
	make -C ${LIBFTDIR}

${NAME}: ${OBJS}
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