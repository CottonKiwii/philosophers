# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 12:00:49 by jwolfram          #+#    #+#              #
#    Updated: 2025/03/28 15:02:12 by jwolfram         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

INCLUDES = -I./includes

LDFLAGS = -lpthread

### FILES ###

FILES = main \
		init \
		time \
		routine \
		odd_routine \
		even_routine \
		print_message \
	  	utils_libft \
	  	utils_other \
		free \

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

fclean: clean
	rm -fr ${NAME}

re: fclean all

### !!!DEV!!! ###
run: re
	./philo

test: re
	cd ./42-philosophers-tester
	make
	./test.sh
	cd ..

norm:
	norminette ${SRC}
### !!!DEV!!! ###

.PHONY: all clean fclean re norm
