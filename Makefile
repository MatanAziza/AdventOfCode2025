NAME1=safe
NAME2=invalid_ids
NAME3=batteries

SRC=GNL/*.c

.PHONY:clean fclean 1 2 3

CC=cc
CFLAGS= -Wall -Wextra -Werror

DAY := $(word 1, $(MAKECMDGOALS))
PART := $(word 2, $(MAKECMDGOALS))
NAME := $(NAME$(DAY))_$(PART)
DAY_PART_O:=Day$(DAY)/Part$(PART).o

all:
	@echo "Comment utiliser le Makefile: make <DAY> <PART>"
	@echo "Ex: make 3 1"

$(DAY):
	@echo "Compilation Day$(DAY)/Part$(PART).c → $(NAME)"
	$(CC) $(CFLAGS) -c -o $(DAY_PART_O) Day$(DAY)/Part$(PART).c
	$(CC) $(CFLAGS) $(SRC) $(DAY_PART_O) -o $(NAME)
	@echo "Binaire créé: $(NAME)"

clean:
	rm -rf */*.o

fclean:clean
	rm -rf $(NAME1)* $(NAME2)* $(NAME3)*

