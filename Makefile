NAME1=safe
NAME2=invalid_ids
NAME3=batteries
NAME4=forklift

SRC=GNL/*.c

CC=cc
CFLAGS= -Wall -Wextra -Werror

all:1 2 3 4

1:11 12

2:21 22

3:31 32

4: 41 42

11:$(NAME1)_1

$(NAME1)_1:Day1/Part1.o
	@$(CC) $(CFLAGS) $(SRC) Day1/Part1.o -o $(NAME1)_1
	@./$(NAME1)_1 Inputs/1

Day1/Part1.o:Day1/Part1.c
	@$(CC) $(CFLAGS) -c $< -o $@

12:$(NAME1)_2

$(NAME1)_2:Day1/Part2.o
	@$(CC) $(CFLAGS) $(SRC) Day1/Part2.o -o $(NAME1)_2
	@./$(NAME1)_2 Inputs/1

Day1/Part2.o:Day1/Part2.c
	@$(CC) $(CFLAGS) -c $< -o $@

21:$(NAME2)_1

$(NAME2)_1:Day2/Part1.o
	@$(CC) $(CFLAGS) $(SRC) Day2/Part1.o -o $(NAME2)_1
	@./$(NAME2)_1 Inputs/2

Day2/Part1.o:Day2/Part1.c
	@$(CC) $(CFLAGS) -c $< -o $@

22:$(NAME2)_2

$(NAME2)_2:Day2/Part2.o
	@$(CC) $(CFLAGS) $(SRC) Day2/Part2.o -o $(NAME2)_2
	@./$(NAME2)_2 Inputs/2

Day2/Part2.o:Day2/Part2.c
	@$(CC) $(CFLAGS) -c $< -o $@

31:$(NAME3)_1

$(NAME3)_1:Day3/Part1.o
	@$(CC) $(CFLAGS) $(SRC) Day3/Part1.o -o $(NAME3)_1
	@./$(NAME3)_1 Inputs/3

Day3/Part1.o:Day3/Part1.c
	@$(CC) $(CFLAGS) -c $< -o $@

32:$(NAME3)_2

$(NAME3)_2:Day3/Part2.o
	@$(CC) $(CFLAGS) $(SRC) Day3/Part2.o -o $(NAME3)_2
	@./$(NAME3)_2 Inputs/3

Day3/Part2.o:Day3/Part2.c
	@$(CC) $(CFLAGS) -c $< -o $@

41:$(NAME4)_1

$(NAME4)_1:Day4/Part1.o
	@$(CC) $(CFLAGS) $(SRC) Day4/Part1.o -o $(NAME4)_1
	@./$(NAME4)_1 Inputs/4

Day4/Part1.o:Day4/Part1.c
	@$(CC) $(CFLAGS) -c $< -o $@

42:$(NAME4)_2

$(NAME4)_2:Day4/Part2.o
	@$(CC) $(CFLAGS) $(SRC) Day4/Part2.o -o $(NAME4)_2
	@./$(NAME4)_2 Inputs/4

Day4/Part2.o:Day4/Part2.c
	@$(CC) $(CFLAGS) -c $< -o $@

help:
	@echo "Comment utiliser le Makefile:"
	@echo "make <DAY><PART> pour une partie"
	@echo "Ex: make 31"
	@echo "Ou bien : make <DAY> pour les 2 parties du jour"
	@echo "Ex: make 1"

clean:
	rm -rf */*.o

fclean:clean
	rm -rf $(NAME1)* $(NAME2)* $(NAME3)* $(NAME4)*

