#include <stdio.h>
#include "dl_fgraph.h"

void print_fgraph(struct fgraph *G) {
	while(G != NULL) {
		struct list *tmp = G->friends;
		printf("%s (%d) -> ",G->name,G->id);
		while(tmp != NULL) {
			printf("%d ",tmp->id);
			tmp = tmp->next;
		}
		printf("\n");
		G = G->next;
	}
}


int main(int argc, char *argv[]) {
	struct fgraph *G;

	if(argc != 2) {
		fprintf(stderr,"Usage: %s <filename>\n",argv[0]);
		return 1;
	}
	
	if((G = read_fgraph(argv[1])) == NULL) {
		fprintf(stderr,"Error reading %s\n",argv[1]);
		return 1;
	}

	print_fgraph(G);

	return 0;
}
