all:
	gcc main.c -o thr_eat_list
DEBUG:
	gcc -fsanitize=thread -g main.c -o thr_eat_list
	./thr_eat_list 100000
DEFAULT:
	gcc main.c -o thr_eat_list
	./thr_eat_list 100000
