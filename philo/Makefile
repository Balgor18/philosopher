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
		init.c\
		main.c\
		simulation.c\
		simulation2.c\
		time.c\
		utils.c\
		verif.c

DEPS = $(SRCS:%.c=DEPS/%.d)

ADD = -lpthread

DEBUG = $(shell env | grep DEBUG= | tr '=' ' ' | awk '{print $$2}')

ifeq ($(DEBUG), 1)
	FLAGS += -g3 -fsanitize=thread
endif

OS = $(shell uname)

all : $(NAME)
# dir_obj
$(NAME) :  $(DEPS)
	$(info $(YELLOW)Compiling $(NAME)...$(WHITE))
	$(CC) $(FLAGS) -o $(NAME) $(INCLUDES) $(DEPS) $(ADD)
	$(info $(GREEN)-->[OK]$(WHITE))

DEPS/%.d : %.c
	$(info $(CYAN)Create obj folder : $(WHITE))
	mkdir -p DEPS
	$(info $(PURPLE)Compiling : $< $(WHITE))
	$(CC) $(FLAGS) -o $@ -c $< $(INCLUDES)
	$(info $(GREEN)[OK]$(WHITE))

clean :
	$(info $(RED)Clean file ...$(WHITE))
	rm -rf DEPS/
	$(info $(GREEN)-->[OK] $(WHITE))

fclean : clean
	$(info $(RED)Clean exec ...$(WHITE))
	rm -rf $(NAME)
	$(info $(GREEN)-->[OK]$(WHITE))

re : fclean $(NAME)

.phony : re fclean clean
