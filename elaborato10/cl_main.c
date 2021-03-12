#include <stdio.h>
#include "cl_fgraph.h"

void print_fgraph(struct fgraph *G) {
	if(G != NULL) {
		struct fgraph *head = G;
		do {
			printf("%s (%d) -> ",G->name,G->id);
			if(G->friends != NULL) {
				struct list *tmp = G->friends;
				do {
					printf("%d ",tmp->id);
					tmp = tmp->next;
				} while(tmp != G->friends);
			}
			printf("\n");
			G = G->next;
		} while(G != head);
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
