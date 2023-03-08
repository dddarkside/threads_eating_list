all:
	gcc main.c -o thr_eat_list
DEBUG:
	gcc -fsanitize=thread main.c -o thr_eat_list
DEFAULT:
	gcc main.c -o thr_eat_list
	./thr_eat_list 100000
