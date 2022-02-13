##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SRC	=	test_bitmap_reader.cpp	\
		../games/Qix/src/bitmapReader.cpp

NAME	=	tests_run

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS	=	 -I ../games/Qix/include -W -Wall -Wextra --coverage -I ../core/include

all:	$(NAME)

tests_run:
	g++ $(SRC) -o $(NAME) -lgtest -lgtest_main -lpthread --coverage -I ../games/Qix/include -W -Wall -Wextra --coverage -I ../core/include
	./$(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)
