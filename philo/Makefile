# Colors
GREY = $(shell tput setaf 59)
RED = $(shell tput setaf 196)
GREEN = $(shell tput setaf 82)
YELLOW = $(shell tput setaf 226)
BLUE = $(shell tput setaf 39)
PURPLE = $(shell tput setaf 164)
CYAN = $(shell tput setaf 37)
WHITE = $(shell tput sgr0)

NAME = philo

CC = clang

INCLUDES = -Iincludes/.

FLAGS = -Wall -Wextra -Werror -MMD -MP

SRCS =	error.c\
		ft_atoi.c\
		ft_bzero.c\
		get_time.c\
		main.c\
		parse.c\
		start_philo.c

OBJS = $(SRCS:%.c=OBJS/%.d)

DEBUG = $(shell env | grep DEBUG | tr '=' ' ' | awk '{print $$2}')

ifeq ($(DEBUG), 1)
	FLAGS += -g3 -fsanitize=address
endif

OBJS/%.d : %.c
	$(info $(PURPLE)Compiling: $< $(WHITE))
	$(CC) $(FLAGS) -o $@ -c $< $(INCLUDES)
	$(info $(GREEN)[OK]$(WHITE))

all : $(NAME)

dir_obj :
	$(info $(CYAN)Create obj folder: +++$(WHITE))
	mkdir -p OBJS

$(NAME) : dir_obj $(OBJS)
	$(info $(YELLOW)Compiling $(NAME)...$(WHITE))
	$(CC) $(FLAGS) -o $(NAME) $(INCLUDES) $(OBJS)
	$(info $(GREEN)-->[OK]$(WHITE))

clean :
	$(info $(RED)$(RED)Clean file...$(WHITE))
	rm -rf OBJS/
	$(info $(GREEN)-->[OK] $(WHITE))

fclean : clean
	$(info $(RED)Clean exec...$(WHITE))
	rm -rf $(NAME)
	$(info $(GREEN)-->[OK] $(WHITE))

re : fclean $(NAME)

.phony : $(NAME)
