# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 12:00:49 by jwolfram          #+#    #+#              #
#    Updated: 2025/01/07 15:17:23 by jwolfram         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra

INCLUDES = -I./includes

LDFLAGS = -lpthread

### FILES ###

FILES = main \
	  utils \

SRC_DIR = src

SRC = ${FILES:%=${OBJ_DIR}/%.c}

OBJ_DIR = obj

OBJ_SORT = ${sort ${dir ${OBJ}}}

OBJ = ${FILES:%=${OBJ_DIR}/%.o}

### TARGETS ###

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${LDFLAGS} $^ ${INCLUDES} -o $@

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_SORT}
	${CC} ${CFLAGS} $< ${INCLUDES} -c  -o $@

${OBJ_SORT}:
	mkdir -p $@

clean:
	rm -fr ${OBJ_DIR}

fclean:
	rm -fr ${NAME}

re: fclean all

### !!!DEV!!! ###
run: re
	./philo

norm:
	norminette ${SRC}
### !!!DEV!!! ###

.PHONY: all clean fclean re norm
