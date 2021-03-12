#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME_LEN 10

int **int_matrix_alloc(int row, int col) {
	int i;
	int **M = (int **)malloc(row*sizeof(int *));

	M[0]=(int *)calloc(row*col,sizeof(int));

	for(i = 0; i < row; i++)
		M[i] = &((M[0])[col*i]);
	return M;
}

char *rand_name(char *name, int length) {
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		char *tmp = name;
		int n = strlen(charset);

    while (length-- > 0) 
				*tmp++ = charset[rand() % n];
    *tmp = '\0';
	return name;
}

int **rand_graph(int n, double p, int *e) {
	int **M = NULL;
	
	*e = 0;
	if((M = int_matrix_alloc(n,n)) != NULL) {
		int i,j;
		
		for(i = 0; i < n; i++)
			for(j = i+1; j < n; j++)
				if((1.0*rand())/RAND_MAX <= p) {
					M[i][j] = M[j][j] = 1;
					(*e)++;
				}
	}
	return M;
}

void print_graph(int **M, int n, int e) {
	int i, j;
	char name[NAME_LEN+1];

	printf("%d %d\n",n,e);
	
	for(i = 0; i < n; i++)
		printf("%d %s\n",i,rand_name(name,NAME_LEN));
	
	for(i = 0; i < n; i++)
		for(j = i+1; j < n; j++)	
			if(M[i][j] == 1)
				printf("%d %d\n",i,j);
}


int main(int argc, char *argv[]) {
	int n, e, **M;
	double p;

	if(argc != 3) {
		fprintf(stderr,"Usage: randgraph <n> <perc>\n");
		return 1;
	}
	srand(time(NULL));
	n = atoi(argv[1]);
	p = atof(argv[2]);

	if((M = rand_graph(n,p,&e)) == NULL) {
		fprintf(stderr,"Error generatig graph\n");
		return 1;
	}
	print_graph(M,n,e);
	
	return 0;
}
