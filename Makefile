NAME1=safe
NAME2=invalid_ids
NAME3=batteries

SRC=GNL/*.c

CC=cc
CFLAGS= -Wall -Wextra -Werror

DAY := $(word 1, $(MAKECMDGOALS))
PART := $(word 2, $(MAKECMDGOALS))
NAME := $(NAME$(DAY))_$(PART)
DAY_PART_O:=Day$(DAY)/Part$(PART).o

all:1 2 3

1:11 12

2:21 22

3:31 32

11:$(NAME1)_1

$(NAME1)_1:Day1/Part1.o
	$(CC) $(CFLAGS) $(SRC) Day1/Part1.o -o $(NAME1)_1
	./$(NAME1)_1 Inputs/1

Day1/Part1.o:Day1/Part1.c
	$(CC) $(CFLAGS) -c $< -o $@

12:$(NAME1)_2

$(NAME1)_2:Day1/Part2.o
	$(CC) $(CFLAGS) $(SRC) Day1/Part2.o -o $(NAME1)_2
	./$(NAME1)_2 Inputs/1

Day1/Part2.o:Day1/Part2.c
	$(CC) $(CFLAGS) -c $< -o $@

21:$(NAME2)_1

$(NAME2)_1:Day2/Part1.o
	$(CC) $(CFLAGS) $(SRC) Day2/Part1.o -o $(NAME2)_1
	./$(NAME2)_1 Inputs/2

Day2/Part1.o:Day2/Part1.c
	$(CC) $(CFLAGS) -c $< -o $@

22:$(NAME2)_2

$(NAME2)_2:Day2/Part2.o
	$(CC) $(CFLAGS) $(SRC) Day2/Part2.o -o $(NAME2)_2
	./$(NAME2)_2 Inputs/2

Day2/Part2.o:Day2/Part2.c
	$(CC) $(CFLAGS) -c $< -o $@

31:$(NAME3)_1

$(NAME3)_1:Day3/Part1.o
	$(CC) $(CFLAGS) $(SRC) Day3/Part1.o -o $(NAME3)_1
	./$(NAME3)_1 Inputs/3

Day3/Part1.o:Day3/Part1.c
	$(CC) $(CFLAGS) -c $< -o $@

32:$(NAME3)_2

$(NAME3)_2:Day3/Part2.o
	$(CC) $(CFLAGS) $(SRC) Day3/Part2.o -o $(NAME3)_2
	./$(NAME3)_2 Inputs/3

Day3/Part2.o:Day3/Part2.c
	$(CC) $(CFLAGS) -c $< -o $@
help:
	@echo "Comment utiliser le Makefile:"
	@echo "make <DAY> <PART> pour une partie"
	@echo "Ex: make 3 1"
	@echo "Ou bien : make <DAY> pour les 2 parties du jour"
	@echo "Ex: make 1"

clean:
	rm -rf */*.o

fclean:clean
	rm -rf $(NAME1)* $(NAME2)* $(NAME3)*

