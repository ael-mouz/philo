NAME	=	philo_bonus
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

RED		=	$(shell tput -Txterm setaf 1)
WHITE	=	$(shell tput -Txterm setaf 7)
BLUE	=	$(shell tput -Txterm setaf 6)
GREEN	=	$(shell tput -Txterm setaf 2)
YELLOW	=	$(shell tput -Txterm setaf 3)

BANER	=	"\n" \
			"$(GREEN)██████$(YELLOW)╗ $(GREEN)██$(YELLOW)╗  $(GREEN)██$(YELLOW)╗$(GREEN)██$(YELLOW)╗$(GREEN)██$(YELLOW)╗      $(GREEN)██████$(YELLOW)╗ \n"\
			"$(GREEN)██$(YELLOW)╔══$(GREEN)██$(YELLOW)╗$(GREEN)██$(YELLOW)║  $(GREEN)██$(YELLOW)║$(GREEN)██$(YELLOW)║$(GREEN)██$(YELLOW)║     $(GREEN)██$(YELLOW)╔═══$(GREEN)██$(YELLOW)╗\n"\
			"$(GREEN)██████$(YELLOW)╔╝$(GREEN)███████$(YELLOW)║$(GREEN)██$(YELLOW)║$(GREEN)██$(YELLOW)║     $(GREEN)██$(YELLOW)║   $(GREEN)██$(YELLOW)║\n"\
			"$(GREEN)██$(YELLOW)╔═══╝ $(GREEN)██$(YELLOW)╔══$(GREEN)██$(YELLOW)║$(GREEN)██$(YELLOW)║$(GREEN)██$(YELLOW)║     $(GREEN)██$(YELLOW)║   $(GREEN)██$(YELLOW)║\n"\
			"$(GREEN)██$(YELLOW)║     $(GREEN)██$(YELLOW)║  $(GREEN)██$(YELLOW)║$(GREEN)██$(YELLOW)║$(GREEN)███████$(YELLOW)╗╚$(GREEN)██████$(YELLOW)╔╝\n"\
			"$(YELLOW)╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ \n$(WHITE)" \
			"		made by $(YELLOW) ael-mouz $(WHITE)\n" \

SRC		=	philo_bonus.c \
			philo_death_bonus.c \
			philo_helper_bonus.c \
			philo_utils_bonus.c \

OBJ		=	$(SRC:.c=.o)

HEADER	=	philo_bonus.h

NUM_FILES := $(words $(SRC))
NUM := 0
RES := 0

all : $(NAME)

$(NAME) : $(OBJ)
	@clear
	@echo $(BANER)
	@$(CC) $(CFLAGS) $(OBJ) -o $@
	@echo "Generated executable : ( $(BLUE) $@ $(WHITE) )\n"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@
	@$(eval NUM := $(shell echo $$(($(NUM) + 1))))
	@$(eval RES := $(shell echo $$(($(NUM) * 100 / $(NUM_FILES)))))
	@echo "Compilation progress:$(GREEN) $(RES)% $(WHITE)"
	@sleep 0.3

clean :
	@clear
	@echo "Cleaning up object files:"
	@for obj in $(OBJ); do \
		echo "$(RED)	- $$obj $(WHITE)"; \
		$(RM) $$obj; \
	done

fclean : clean
	@echo "Cleaning up executable file:"
	@echo "$(RED)	- $(NAME)$(WHITE)";
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re