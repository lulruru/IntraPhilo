
RESET	= '\033[0m'
RED		= '\033[0;31m'
GREEN	= '\033[0;32m'
YELLOW	= '\033[0;33m'
BLUE	= '\033[0;34m'
VIOLET	= '\033[0;35m'
CYAN	= '\033[0;36m'
WHITE	= '\033[0;37m'

# NAME
NAME = philo
CHECK_NAME = checker

# DIR
SRC_DIR = src

# src
SRC = ./src/main.c ./src/utils.c ./src/init.c ./src/exit.c ./src/eat.c \
		./src/routine.c 


# obj
SRCCO = $(SRC:.c=.o)
CHECK_CO = $(CHECK_SRCS:.c=.o)

# srcs
SRCS = $(addprefix $(SRC_DIR)/,$(SRC))
CHECK_SRCS = $(addprefix $(SRC_DIR)/, $(CHECK_SRC))

# compil
CC = cc
GCC = cc -Wall -Wextra -Werror

# delete
CLEANER = rm -f

nb = 1

all: logo $(NAME)

$(NAME): $(SRCCO)
	$(GCC) $(SRCCO) -o $@ -lreadline 

%.o : %.c
	@printf "\033[0;36mOBJECT [\033[0m"
	@printf "\033[0;33m%d\033[0m" "$(nb)"
	@printf "\033[0;36m] - ready\033[0m\n"
	@printf "\033[0;36mCompiling...\033[0m"
	@if ( $(GCC) -c $< -o $@ ); \
	then \
		printf "\033[0;32mSUCCESS\033[0m\n"; \
	else \
		printf "\033[0;31mFAILURE\033[0m\n"; \
	fi
	$(eval nb=$(shell echo $$(($(nb)+1))))

clean:
	@printf "\033[1;31m***********************************\033[0m\n"
	@printf "\033[1;31m*                                 *\033[0m\n"
	@printf "\033[1;31m*        Removing Files           *\033[0m\n"
	@printf "\033[1;31m*                                 *\033[0m\n"
	@printf "\033[1;31m***********************************\033[0m\n\n"
	@printf "\033[0;36mRemoving files and executable...\033[0m\n"
	@printf "\033[0;36mSuppression des fichiers et de l'exécutable...\033[0m\n"
	$(CLEANER) $(SRCCO)
	$(CLEANER) $(CHECK_CO)
	@printf "\033[0;32mDone ✔️\033[0m\n"
	@printf "\033[0;32mDone ✔️\033[0m\n"
	
fclean: clean
	@printf "\033[0;36mDeleting Executables...\033[0m\n"
	$(CLEANER) $(NAME)
	$(CLEANER) $(CHECK_NAME)
	@printf "\033[0;32mDone ✔️\033[0m\n"
	@printf "\033[0;32mDone ✔️\033[0m\n"
	@printf "\033[1;32m**************************************\033[0m\n"
	@printf "\033[1;32m*                                    *\033[0m\n"
	@printf "\033[1;32m* ✅  Folder Cleaned Succesfully ✅  *\033[0m\n"
	@printf "\033[1;32m*                                    *\033[0m\n"
	@printf "\033[1;32m**************************************\033[0m\n\n"
	
re: fclean all

.PHONY: all clean fclean re


logo :
	@echo  ${BLUE}"\n   _______    __    __   __    ___       ______    \n  |   __  \  /  |  |  \ |  \  |   |     /      \   \n  (. |__) :)(:  (__)  :)||  | ||  |    // ____  \  \n  |:  ____/  \/      \/ |:  | |:  |   /  /    / :) \n  (|  /      //  __  \\ |.  |  \  |___(: (____/ //  \n /|__/ \    (:  (  )  :)/\  |\( \_|:  \\        /   \n(_______)    \__|  |__/(__\_|_)\_______)\_____/    \n" ${RESET}



                                                    