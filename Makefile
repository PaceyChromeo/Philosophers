NAME = philo

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC =	ft_philo.c \
		ft_philo_utils.c \
		ft_life.c \
		ft_time.c

OBJ = ${SRC:.c=.o}

%.o:%.c
	${CC} ${FLAGS} -o $@ -c $<

all: ${NAME}

${NAME}: ${OBJ}
	${CC} -g -o ${NAME} -lpthread $?

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean
