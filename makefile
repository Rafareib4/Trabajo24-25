all: fragmenta normalizar listaDistanciasMinimas knn_wilson
	
knn_wilson: fragmenta.o listaDistanciasMinimas.o normalizar.o
	gcc -g knn_wilson.c fragmenta.o listaDistanciasMinimas.o normalizar.o -lm -o knn_wilson -Wall
fragmenta: fragmenta.c
	gcc -c fragmenta.c -Wall
normalizar: normalizar.c
	gcc -c normalizar.c -Wall
listaDistanciasMinimas: listaDistanciasMinimas.c
	gcc -c listaDistanciasMinimas.c -Wall
clean:
	rm *.o
	rm knn_wilson
