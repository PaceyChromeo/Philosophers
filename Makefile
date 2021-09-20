NAME = philo

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC =	ft_philo.c \
		ft_philo_utils.c \
		ft_life.c \
		ft_time.c \
		ft_control.c

OBJ = ${SRC:.c=.o}

ifneq (,$(findstring xterm,${TERM}))
	BLACK        := $(shell tput -Txterm setaf 0)
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	WHITE        := $(shell tput -Txterm setaf 7)
	RESET := $(shell tput -Txterm sgr0)
endif

%.o:%.c
	@printf "\033[0;33m Compiling : ${BLUE}$@ \r"
	@${CC} ${FLAGS} -o $@ -c $<

all: ${NAME}

${NAME}: ${OBJ}
	@${CC} -g -o ${NAME} -lpthread $?
	@printf "\033[0;33m Compiling : \033[0;32m [DONE]"

clean:
	@rm -rf ${OBJ}

fclean: clean
	@echo "\033[0;33m Cleaning : \033[0;32m [DONE]"
	@rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean
