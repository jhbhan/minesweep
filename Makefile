mine_sweeper.out: mine_sweeper.o board_print.o
	gcc -Wall -Werror -o mine_sweeper.out mine_sweeper.o board_print.o

mine_sweeper.o: mine_sweeper.c mine_sweeper.h board_print.h
	gcc -Wall -Werror -c mine_sweeper.c

board_print.o: board_print.c board_print.h mine_sweeper.h
	gcc -Wall -Werror -c board_print.c

clean:
	rm -fr *.o *.out
