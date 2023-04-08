# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmenke <cmenke@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 21:07:24 by cmenke            #+#    #+#              #
#    Updated: 2023/04/08 21:31:49 by cmenke           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long

SRCDIR := mandatory

SRCS := $(addprefix ${SRCDIR}/,main.c \
							list_functions.c)


OBJS := ${SRCS:.c=.o}

HEADER := ${SRCDIR}/so_long.h

# CFLAGS := -Wall -Werror -Wextra

CC := cc

RM := rm -f

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

${OBJS}: ${HEADER}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re		