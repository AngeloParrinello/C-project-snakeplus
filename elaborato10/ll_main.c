//#include"selector.h"
//#include <stdio.h>
//
//#include "ll_fgraph.h"
//
//#ifdef LLIST
//
//
//
//void print_fgraph(struct fgraph *G) {
//	while(G != NULL)
//	{
//		struct list *tmp = G->friends;
//		printf("%s (%d) -> ",G->name,G->id);
//		while(tmp != NULL)
//		{
//			printf("%d ",tmp->id);
//			tmp = tmp->next;
//		}
//		printf("\n");
//		G = G->next;
//	}
//}
//
//
////int main(int argc, char *argv[]) {
////	struct fgraph *G;
////
////	if(argc != 2) {
////		fprintf(stderr,"Usage: %s <filename>\n",argv[0]);
////		return 1;
////	}
////	
////	if((G = read_fgraph(argv[1])) == NULL) {
////		fprintf(stderr,"Error reading %s\n",argv[1]);
////		return 1;
////	}
//int main()
//{
//	struct graph *G,*S;
//
//	G = read_fgraph("graph_example.txt");
//
//
//	print_fgraph(G);
//
//	printf("Conta amicizie: %d \n\n\n", count_friendships(G));
//	S = copy_graph(G);
//
//	print_fgraph(S);
//
//	system("pause");
//	return 0;
//}
//
//#endif // LLIST

#include "selector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dl_fgraph.h"
#include "cl_fgraph.h"
#include "ll_fgraph.h"

#define N 1000


#ifdef LLIST

void print_fgraph(struct fgraph *G) {
	while (G != NULL) {
		struct list *tmp = G->friends;
		printf("%s (%d) -> ", G->name, G->id);
		while (tmp != NULL) {
			printf("%d ", tmp->id);
			tmp = tmp->next;
		}
		printf("\n");
		G = G->next;
	}
}

//int main(int argc, char *argv[]) {
//  struct fgraph *G;
//
//  if(argc != 2) {
//    fprintf(stderr,"Usage: %s <filename>\n",argv[0]);
//    return 1;
//  }
//  
//  if((G = read_fgraph(argv[1])) == NULL) {
//    fprintf(stderr,"Error reading %s\n",argv[1]);
//    return 1;
//  }
int main() {
	struct graph *G, *cG;

	G = NULL;
	print_fgraph(G);

	printf("G:\n");
	G = read_fgraph("graph_example.txt");
	print_fgraph(G);

	printf("\nConta degli amici di G: %d\n\n\n", count_friendships(G));

	cG = copy_graph(G);
	printf("Copia di G: \n");
	print_fgraph(cG);

	printf("\nConta degli amici di G: %d\n\n\n", count_friendships(cG));

	system("PAUSE");
	return 0;
}

#endif


#ifdef DLIST

void print_fgraph(struct fgraph *G) {
	while (G != NULL) {
		struct list *tmp = G->friends;
		printf("%s (%d) -> ", G->name, G->id);
		while (tmp != NULL) {
			printf("%d ", tmp->id);
			tmp = tmp->next;
		}
		printf("\n");
		G = G->next;
	}
}

int main() {
	struct graph *G, *cG;

	G = NULL;
	print_fgraph(G);

	printf("G:\n");
	G = read_fgraph("graph_example.txt");
	print_fgraph(G);

	printf("\nConta degli amici di G: %d\n\n\n", count_friendships(G));

	cG = copy_graph(G);
	printf("Copia di G: \n");
	print_fgraph(cG);

	printf("\nConta degli amici di G: %d\n\n\n", count_friendships(cG));

	system("PAUSE");
	return 0;
}

#endif


#ifdef CLIST

void print_fgraph(struct fgraph *G) {
	if (G != NULL) {
		struct fgraph *head = G;
		do {
			printf("%s (%d) -> ", G->name, G->id);
			if (G->friends != NULL) {
				struct list *tmp = G->friends;
				do {
					printf("%d ", tmp->id);
					tmp = tmp->next;
				} while (tmp != G->friends);
			}
			printf("\n");
			G = G->next;
		} while (G != head);
	}
}

int main() {
	struct graph *G, *cG;

	G = NULL;
	print_fgraph(G);

	printf("G:\n");
	G = read_fgraph("graph_example.txt");
	print_fgraph(G);

	printf("\nConta degli amici di G: %d\n\n\n", count_friendships(G));

	cG = copy_graph(G);
	printf("Copia di G: \n");
	print_fgraph(cG);

	printf("\nConta degli amici di G: %d\n\n\n", count_friendships(cG));

	system("PAUSE");
	return 0;
}

#endif