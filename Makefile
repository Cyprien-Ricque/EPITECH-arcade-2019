##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

all:
		make all -C core
		make all -C lib/SFML
		make all -C lib/NCurse
		make all -C lib/opengl
		make all -C games/Qix
		make all -C games/SolarFox

core:
		make all -C core

games:
		make all -C games/Qix
		make all -C games/SolarFox

graphicals:
		make all -C lib/SFML
		make all -C lib/NCurse
		make all -C lib/opengl

clean:
		rm -f $(OBJ)
		make clean -C core
		make clean -C games/Qix
		make clean -C games/SolarFox
		make clean -C lib/SFML
		make clean -C lib/NCurse
		make clean -C lib/opengl
		make clean -C tests/
		find . -name "*.gcno" -exec /bin/rm '{}' \;
		find . -name "*.gcda" -exec /bin/rm '{}' \;

tests_run:
		make all -C tests/

fclean:	clean
		rm -f arcade
		make fclean -C games/Qix
		make fclean -C games/SolarFox
		make fclean -C lib/SFML
		make fclean -C lib/NCurse
		make fclean -C lib/opengl
		make fclean -C core
		make fclean -C tests

re:	fclean all

.PHONY:	all core games graphicals
