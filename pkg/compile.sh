gcc -g -c Queue.c -o Queue.o
gcc -g -c prod_cons_on_Q_Solution.c -o prod_cons_on_Q_Solution.o
gcc -g prod_cons_on_Q.o Queue.o -o exe -lpthread
gcc -g prod_cons_on_Q_Solution.o Queue.o -o solution.exe -lpthread
