##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

GPP			=	g++

RM			=	rm -rf

NAME		=	autoCompletion

COMPILEFLAG	=	-Wall -Wextra

INCLUDE		=	-Iinclude/

CPPFLAGS    =	$(COMPILEFLAG) $(INCLUDE)

SRC			=	src/main.cpp			\
				src/address.cpp			\
				src/autoCompletion.cpp		\
				src/Exception.cpp

OBJ			=	$(SRC:.cpp=.o)

all:
	@make --no-print-directory $(NAME)

$(NAME):	$(OBJ)
	@echo -e "\033[01m\033[31mLinking ...\033[00m"
	@$(GPP) $(OBJ) -o $(NAME) $(CPPFLAGS) $(CPPFLAGS)
	@echo -e "\033[01m\033[32mStandard compilation done => ${NAME}\033[00m"

clean:
	@$(RM) vgcore.* src/vgcore.*
	@$(RM) src/*.o unit_tests *.gcno *.gcda
	@echo -e "\033[01m\033[31mRemoving useless files ...\033[00m"

fclean:	clean
	@$(RM) $(NAME)
	@echo -e "\033[01m\033[31mRemoving libraries and binary : {${NAME}} ...\033[00m"

re:	fclean
	@make all --no-print-directory

.PHONY:	all clean fclean re
