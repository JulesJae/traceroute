NAME = ft_traceroute

PATH_SRC = ./src/

PATH_INC = ./includes/

INCLUDES = -I $(PATH_INC)

GCC = gcc
FLAGS = -Wall -Wextra -Werror $(INCLUDES) -g

SRC =   main.c \
		address.c \
		conf.c \
		ft_traceroute.c \
		opt.c \
		receive.c \
		utils.c \
		wrapper.c \

OBJ = $(addprefix $(PATH_SRC), $(SRC:.c=.o))

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(PATH_INC)ft_traceroute.h
		$(GCC) $(OBJ) -o $(NAME) -lm

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
