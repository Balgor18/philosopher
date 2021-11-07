NAME = philosopher

CC = clang

INCLUDES = -I includes/philosopher.h

FLAGS = -Wall -Wextra -Werror

SRCS = main.c

OBJ = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS)
