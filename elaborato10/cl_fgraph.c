#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cl_fgraph.h"

#define N 1000

struct fgraph *read_fgraph(char *filename) {
	FILE *in = fopen(filename,"r");
	struct fgraph *G = NULL;
	unsigned int i, n, m;
	
	if(in != NULL && fscanf(in,"%u %u\n",&n,&m) != EOF) {
		unsigned int id, id1, id2;
		char name[N];

		for(i = 0; i < n && fscanf(in,"%u ",&id) != EOF &&  fgets(name,N,in) != NULL; i++) {
			name[strlen(name)-1]='\0';
			insert_individual(&G,strcpy(calloc(strlen(name)+1,sizeof(char)),name),id);
		}
		
		for(i = 0; i < m && fscanf(in,"%u %u",&id1,&id2) != EOF; i++)
			insert_friendship(G,id1,id2);

		fclose(in);
	}

	return G;
}

static struct fgraph *fgraph_alloc(char *name, unsigned int id) {
	struct fgraph *tmp = (struct fgraph *)malloc(sizeof(struct fgraph));

	if(tmp != NULL) {
		tmp->name    = name;
		tmp->id      = id;
		tmp->friends = NULL;		
		tmp->next    = tmp;
		tmp->prev    = tmp;
	}
	return tmp;
} 

static struct list *list_alloc(unsigned int id) {
	struct list *tmp = (struct list *)malloc(sizeof(struct list));

	if(tmp != NULL) {
		tmp->id   = id;
		tmp->next = tmp;
		tmp->prev = tmp;
	}
	return tmp; 
}
static int head_insert_individual(struct fgraph **G, char *name, unsigned int id) {
	struct fgraph *tmp = fgraph_alloc(name,id);
	
	if(tmp != NULL) {
		if(*G != NULL) {
			struct fgraph *prv = (*G)->prev, *nxt = *G;
			tmp->prev = prv;
			tmp->next = nxt;
			prv->next = tmp;
			nxt->prev = tmp;
		}
		*G = tmp;
	}
	return tmp == NULL;
}

static int head_insert_list(struct list **L, unsigned int id) {
	struct list *tmp = list_alloc(id);

	if(tmp != NULL) {
    if(*L != NULL) {
      struct list *prv = (*L)->prev, *nxt = *L;
      tmp->prev = prv;
      tmp->next = nxt;
      prv->next = tmp;
      nxt->prev = tmp;
    }
    *L = tmp;
  }
	return tmp == NULL;
}

static  struct fgraph *search_individual(struct fgraph *G, unsigned int id) {
	if(G == NULL) {
		return NULL;
	} else {
		struct fgraph *tmp = G;

		do {
			if(tmp->id == id)
				return tmp;
		} while((tmp = tmp->next)!= G);

		return NULL;
	}
}

static  struct list *search_list(struct list *L, unsigned int id) {	
	if(L == NULL) {
		return NULL;
	} else {
		struct list *tmp = L;

		do {
			if(tmp->id == id)
				return tmp;
		} while((tmp = tmp->next)!= L);

		return NULL;
	}
}


int insert_individual(struct fgraph **G, char *name, unsigned int id) {
	if(G == NULL)
		return 1;
	else if(search_individual(*G,id) != NULL) 
		return 0;
	else 
		return head_insert_individual(G,name,id);
}

int insert_friendship(struct fgraph *G, unsigned int id1, unsigned int id2) {
	struct fgraph *tmp1 = search_individual(G,id1);
	struct fgraph *tmp2 = search_individual(G,id2);
	
	if(tmp1 == NULL || tmp2 == NULL) {
		return 1;
	} else {
		if(search_list(tmp1->friends,id2) == NULL) 
			head_insert_list(&tmp1->friends,id2);
		if(search_list(tmp2->friends,id1) == NULL)
      head_insert_list(&tmp2->friends,id1);
		return 0;
	}
}
