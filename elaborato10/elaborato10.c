#include "selector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dl_fgraph.h"
#include "cl_fgraph.h"
#include "ll_fgraph.h"

#define N 1000


// Implementazioni per liste concatenate
#ifdef LLIST

static struct fgraph *fgraph_alloc(char *name, unsigned int id);
static struct list *list_alloc(unsigned int id);

static int node_insert_list(struct list *L, unsigned int id) 
{
	if (L == NULL)
		return 1;
	else {
		struct list *tmp = list_alloc(id);

		while (L->next != NULL)L = L->next;

		if (tmp != NULL) {
			tmp->next = L->next;
			L->next = tmp;
		}
		return tmp == NULL;
	}
}

static int node_insert_individual(struct fgraph *G, char *name, unsigned int id) {
	if (G == NULL)
		return 1;
	else {
		struct fgraph *tmp = fgraph_alloc(name, id);

		while (G->next != NULL)G  = G ->next;

		if (tmp != NULL) {
			tmp->next = G->next;
			G->next = tmp;
		}
		return tmp == NULL;
	}
}

//while ((*L)->next != NULL)(*L) = (*L)->next;

static int head_insert_individual(struct fgraph **G, char *name, unsigned int id) {
	struct fgraph *tmp = fgraph_alloc(name, id);

	if (tmp != NULL) {
		tmp->next = *G;
		*G = tmp;
	}
	return tmp == NULL;
}

static  int head_insert_list(struct list **L, unsigned int id) {
	struct list *tmp = list_alloc(id);

	if (tmp != NULL) {
		tmp->next = *L;
		*L = tmp;
	}
	return tmp == NULL;
}

/*da togliere...*/

//static struct fgraph *search_individual(struct fgraph *G, unsigned int id) {
//	while (G != NULL && G->id != id)
//		G = G->next;
//	return G;
//}
//
//static struct list *search_list(struct list *L, unsigned int id) {
//	while (L != NULL && L->id != id)
//		L = L->next;
//	return L;
//}
//
//struct fgraph *read_fgraph(char *filename) {
//	FILE *in = fopen(filename, "r");
//	struct fgraph *G = NULL;
//	unsigned int i, n, m;
//
//	if (in != NULL && fscanf(in, "%u %u\n", &n, &m) != EOF) {
//		unsigned int id, id1, id2;
//		char name[N];
//
//		for (i = 0; i < n && fscanf(in, "%u ", &id) != EOF && fgets(name, N, in) != NULL; i++) {
//			name[strlen(name) - 1] = '\0';
//			insert_individual(&G, strcpy(calloc(strlen(name) + 1, sizeof(char)), name), id);
//		}
//
//		for (i = 0; i < m && fscanf(in, "%u %u", &id1, &id2) != EOF; i++)
//			insert_friendship(G, id1, id2);
//
//		fclose(in);
//	}
//
//	return G;
//}
//
//int insert_individual(struct fgraph **G, char *name, unsigned int id) {
//	if (G == NULL)
//		return 1;
//	else if (search_individual(*G, id) != NULL)
//		return 0;
//	else
//		return head_insert_individual(G, name, id);
//}
//
//int insert_friendship(struct fgraph *G, unsigned int id1, unsigned int id2) {
//	struct fgraph *tmp1 = search_individual(G, id1);
//	struct fgraph *tmp2 = search_individual(G, id2);
//
//	if (tmp1 == NULL || tmp2 == NULL) {
//		return 1;
//	}
//	else {
//		if (search_list(tmp1->friends, id2) == NULL)
//			head_insert_list(&tmp1->friends, id2);
//		if (search_list(tmp2->friends, id1) == NULL)
//			head_insert_list(&tmp2->friends, id1);
//		return 0;
//	}
//}

/*... fino a qui*/

static struct fgraph *fgraph_alloc (char *name, unsigned int id)
{
	struct fgraph *tmp = (struct fgraph *)malloc(sizeof(struct fgraph));

	if (tmp != NULL) {
		tmp->name = strcpy(calloc(strlen(name) + 1, sizeof(char)), name);
		tmp->id = id;
		tmp->friends = NULL;
		tmp->next = NULL;
	}
	return tmp;
}

static struct list *list_alloc(unsigned int id)
{
	struct list *tmp = (struct list *)malloc(sizeof(struct list));

	if (tmp != NULL) {
		tmp->id = id;
		tmp->next = NULL;
	}
	return tmp;
}


int count_friendships(struct fgraph *G)
{
	int amici = 0;
	struct fgraph *tmp = G;
	while (tmp != NULL)
	{
		struct list *amichetti = tmp->friends;

		while (amichetti != NULL)
		{
			amici++;
			amichetti = amichetti->next;

		}

		tmp = tmp->next;
	}
	amici = amici / 2;
	return amici;
}

struct fgraph *copy_graph(struct fgraph *G)
{
	struct fgraph *tmp = G;
	struct fgraph *grafo = NULL;
	struct fgraph *grafetto=NULL;
	int w = 0;
	int y = 0;
	while (tmp != NULL)
	{
		
		//lista grande
		if (y == 0) //se sono alla testa del grafo faccio un inserimento in testa
		{
			head_insert_individual(&grafo, tmp->name, tmp->id);
			y++;
		}
		else node_insert_individual(grafo, tmp->name, tmp->id);
		//lista piccola

		if (w == 0)
		{
			grafetto = grafo;
			w++;
		}
		else {
			struct fgraph *tmp3 = grafo;
			while (tmp3->next != NULL) tmp3 = tmp3->next;
			grafetto = tmp3;
		}

		struct list *tmp1 = tmp->friends;
		int k = 0;
		while (tmp1 != NULL)
		{
			
			if (k == 0)
			{
				head_insert_list(&grafetto->friends, tmp1->id);
				k++;
			}
			else
			{	
				while (grafetto->next != NULL)grafetto = grafetto->next;
				node_insert_list(grafetto->friends, tmp1->id);
			}
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;

	}

	return grafo;

}


#endif


// Implementazioni per liste doppiamente concatenate
#ifdef DLIST
static struct list *list_alloc(unsigned int id);
static struct fgraph *fgraph_alloc(char *name, unsigned int id);
static int node_insert_list(struct list *L, unsigned int id)
{
	if (L == NULL)
		return 1;
	else {
		struct list *tmp = list_alloc(id);

		while (L->next != NULL)L = L->next;

		if (tmp != NULL) {
			tmp->next = L->next;
			L->next = tmp;
		}
		return tmp == NULL;
	}
}

static int node_insert_individual(struct fgraph *G, char *name, unsigned int id) {
	if (G == NULL)
		return 1;
	else {
		struct fgraph *tmp = fgraph_alloc(name, id);

		while (G->next != NULL)G = G->next;

		if (tmp != NULL) {
			tmp->next = G->next;
			G->next = tmp;
		}
		return tmp == NULL;
	}
}
////questo va levato
//struct fgraph *read_fgraph(char *filename) {
//	FILE *in = fopen(filename, "r");
//	struct fgraph *G = NULL;
//	unsigned int i, n, m;
//
//	if (in != NULL && fscanf(in, "%u %u\n", &n, &m) != EOF) {
//		unsigned int id, id1, id2;
//		char name[N];
//
//		for (i = 0; i < n && fscanf(in, "%u ", &id) != EOF && fgets(name, N, in) != NULL; i++) {
//			name[strlen(name) - 1] = '\0';
//			insert_individual(&G, strcpy(calloc(strlen(name) + 1, sizeof(char)), name), id);
//		}
//
//		for (i = 0; i < m && fscanf(in, "%u %u", &id1, &id2) != EOF; i++)
//			insert_friendship(G, id1, id2);
//
//		fclose(in);
//	}
//
//	return G;
//}

static struct fgraph *fgraph_alloc(char *name, unsigned int id) {
	struct fgraph *tmp = (struct fgraph *)malloc(sizeof(struct fgraph));

	if (tmp != NULL) {
		tmp->name = strcpy(calloc(strlen(name) + 1, sizeof(char)), name);
		tmp->id = id;
		tmp->friends = NULL;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	return tmp;
}

static struct list *list_alloc(unsigned int id) {
	struct list *tmp = (struct list *)malloc(sizeof(struct list));

	if (tmp != NULL) {
		tmp->id = id;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	return tmp;
}

static int head_insert_individual(struct fgraph **G, char *name, unsigned int id) {
	struct fgraph *tmp = fgraph_alloc(name, id);

	if (tmp != NULL) {
		tmp->next = *G;
		if (*G != NULL)
			(*G)->prev = tmp;
		*G = tmp;
	}
	return tmp == NULL;
}

static  int head_insert_list(struct list **L, unsigned int id) {
	struct list *tmp = list_alloc(id);

	if (tmp != NULL) {
		tmp->next = *L;
		if (*L != NULL)
			(*L)->prev = tmp;
		*L = tmp;
	}
	return tmp == NULL;
}

//static struct fgraph *search_individual(struct fgraph *G, unsigned int id) {
//	while (G != NULL && G->id != id)
//		G = G->next;
//	return G;
//}

//static struct list *search_list(struct list *L, unsigned int id) {
//	while (L != NULL && L->id != id)
//		L = L->next;
//	return L;
//}


//int insert_individual(struct fgraph **G, char *name, unsigned int id) {
//	if (G == NULL)
//		return 1;
//	else if (search_individual(*G, id) != NULL)
//		return 0;
//	else
//		return head_insert_individual(G, name, id);
//}
//
//int insert_friendship(struct fgraph *G, unsigned int id1, unsigned int id2) {
//	struct fgraph *tmp1 = search_individual(G, id1);
//	struct fgraph *tmp2 = search_individual(G, id2);
//
//	if (tmp1 == NULL || tmp2 == NULL) {
//		return 1;
//	}
//	else {
//		if (search_list(tmp1->friends, id2) == NULL)
//			head_insert_list(&tmp1->friends, id2);
//		if (search_list(tmp2->friends, id1) == NULL)
//			head_insert_list(&tmp2->friends, id1);
//		return 0;
//	}
//}

int count_friendships(struct fgraph *G) {
	int amici = 0;
	struct fgraph *tmp = G;
	while (tmp != NULL)
	{
		struct list *amichetti = tmp->friends;

		while (amichetti != NULL)
		{
			amici++;
			amichetti = amichetti->next;

		}

		tmp = tmp->next;
	}
	amici = amici / 2;
	return amici;
}

struct fgraph *copy_graph(struct fgraph *G)
{
	struct fgraph *tmp = G;
	struct fgraph *grafo = NULL;
	struct fgraph *grafetto = NULL;
	int w = 0;
	int y = 0;
	while (tmp != NULL)
	{
		//lista grande
		if (y == 0) //se sono alla testa del grafo faccio un inserimento in testa
		{
			head_insert_individual(&grafo, tmp->name, tmp->id);
			y++;
		}
		else node_insert_individual(grafo, tmp->name, tmp->id);
		//lista piccola

		if (w == 0)
		{
			grafetto = grafo;
			w++;
		}
		else {
			struct fgraph *tmp3 = grafo;
			while (tmp3->next != NULL) tmp3 = tmp3->next;
			grafetto = tmp3;
		}

		struct list *tmp1 = tmp->friends;
		int k = 0;
		while (tmp1 != NULL)
		{

			if (k == 0)
			{
				head_insert_list(&grafetto->friends, tmp1->id);
				k++;
			}
			else
			{
				while (grafetto->next != NULL)grafetto = grafetto->next;
				node_insert_list(grafetto->friends, tmp1->id);
			}
			tmp1 = tmp1->next;
		}
		tmp = tmp->next;

	}

	return grafo;

}





#endif

// Implementazioni per liste doppiamente concatenate circolari
#ifdef CLIST
static struct list *list_alloc(unsigned int id);
static struct fgraph *fgraph_alloc(char *name, unsigned int id);

static int node_insert_list(struct list *L, unsigned int id) {
	if (L == NULL)
		return 1;
	else {
		
		struct list *tmp = list_alloc(id), *nxt = L->next, *prv = L, *tmp2 = L;
		while (tmp2->next != L)tmp2 = tmp2->next;
		if (tmp != NULL && tmp2 != NULL) {
			tmp2->next = tmp;
			tmp->next = L;
		}
		return tmp == NULL;
	}
}

static int node_insert_individual(struct fgraph *G, char *name, unsigned int id) {
	if (G == NULL)
		return 1;
	else {
		struct fgraph *tmp = fgraph_alloc(name, id), *nxt = G->next, *prv = G;

		

		if (tmp != NULL) {
			tmp->prev = prv;
			tmp->next = nxt;
			prv->next = tmp;
			nxt->prev = tmp;
		}
		return tmp == NULL;
	}
}

static struct fgraph *fgraph_alloc(char *name, unsigned int id) {
	struct fgraph *tmp = (struct fgraph *)malloc(sizeof(struct fgraph));

	if (tmp != NULL) {
		tmp->name = strcpy(calloc(strlen(name) + 1, sizeof(char)), name);
		tmp->id = id;
		tmp->friends = NULL;
		tmp->next = tmp;
		tmp->prev = tmp;
	}
	return tmp;
}

static struct list *list_alloc(unsigned int id) {
	struct list *tmp = (struct list *)malloc(sizeof(struct list));

	if (tmp != NULL) {
		tmp->id = id;
		tmp->next = tmp;
		tmp->prev = tmp;
	}
	return tmp;
}

static int head_insert_individual(struct fgraph **G, char *name, unsigned int id) {
	struct fgraph *tmp = fgraph_alloc(name, id);

	if (tmp != NULL) {
		if (*G != NULL) {
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

	if (tmp != NULL) {
		if (*L != NULL) {
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
////Da qua
//struct fgraph *read_fgraph(char *filename) {
//	FILE *in = fopen(filename, "r");
//	struct fgraph *G = NULL;
//	unsigned int i, n, m;
//
//	if (in != NULL && fscanf(in, "%u %u\n", &n, &m) != EOF) {
//		unsigned int id, id1, id2;
//		char name[N];
//
//		for (i = 0; i < n && fscanf(in, "%u ", &id) != EOF && fgets(name, N, in) != NULL; i++) {
//			name[strlen(name) - 1] = '\0';
//			insert_individual(&G, strcpy(calloc(strlen(name) + 1, sizeof(char)), name), id);
//		}
//
//		for (i = 0; i < m && fscanf(in, "%u %u", &id1, &id2) != EOF; i++)
//			insert_friendship(G, id1, id2);
//
//		fclose(in);
//	}
//
//	return G;
//}
//
//static  struct fgraph *search_individual(struct fgraph *G, unsigned int id) {
//	if (G == NULL) {
//		return NULL;
//	}
//	else {
//		struct fgraph *tmp = G;
//
//		do {
//			if (tmp->id == id)
//				return tmp;
//		} while ((tmp = tmp->next) != G);
//
//		return NULL;
//	}
//}
//
//static  struct list *search_list(struct list *L, unsigned int id) {
//	if (L == NULL) {
//		return NULL;
//	}
//	else {
//		struct list *tmp = L;
//
//		do {
//			if (tmp->id == id)
//				return tmp;
//		} while ((tmp = tmp->next) != L);
//
//		return NULL;
//	}
//}
//
//int insert_individual(struct fgraph **G, char *name, unsigned int id) {
//	if (G == NULL)
//		return 1;
//	else if (search_individual(*G, id) != NULL)
//		return 0;
//	else
//		return head_insert_individual(G, name, id);
//}
//
//int insert_friendship(struct fgraph *G, unsigned int id1, unsigned int id2) {
//	struct fgraph *tmp1 = search_individual(G, id1);
//	struct fgraph *tmp2 = search_individual(G, id2);
//
//	if (tmp1 == NULL || tmp2 == NULL) {
//		return 1;
//	}
//	else {
//		if (search_list(tmp1->friends, id2) == NULL)
//			head_insert_list(&tmp1->friends, id2);
//		if (search_list(tmp2->friends, id1) == NULL)
//			head_insert_list(&tmp2->friends, id1);
//		return 0;
//	}
//}
//fin qua
int count_friendships(struct fgraph *G) {
	int amici = 0;
	struct fgraph *tmp = G;
	
	do {
		struct list *amichetti = tmp->friends;
		
		do {
			amici++;
			amichetti = amichetti->next;

		} while (amichetti != tmp->friends);
		tmp = tmp->next;
	} while (tmp != G && tmp->friends!=NULL);
	amici = amici / 2;
	return amici;
}

struct fgraph *copy_graph(struct fgraph *G)
{
	struct fgraph *tmp = G;
	struct fgraph *grafo = NULL;
	struct fgraph *grafetto = NULL;
	int w = 0;
	int y = 0;
	
	do
	{
		//lista grande
		if (y == 0) //se sono alla testa del grafo faccio un inserimento in testa
		{
			head_insert_individual(&grafo, tmp->name, tmp->id);
			y++;
		}
		else node_insert_individual(grafo->prev, tmp->name, tmp->id);

		//lista piccola
		if (w == 0)
		{
			grafetto = grafo;
			w++;
		}
		else 
		{
			struct fgraph *tmp3 = grafo;
			while (tmp3->next != grafo)
			{ 
				tmp3 = tmp3->next; 
			}
			grafetto = tmp3;
		}

		struct list *tmp1 = tmp->friends;
		struct fgraph *head = grafo;
		int k = 0;
		do
		{
			if (k == 0)
			{
				if(tmp1!=NULL)head_insert_list(&grafetto->friends, tmp1->id);
				k++;
			}
			else
			{	
				while (grafetto->next != head)grafetto = grafetto->next;
				node_insert_list(grafetto->friends, tmp1->id);
			}
			if(tmp1!=NULL)tmp1 = tmp1->next;
		} while (tmp1 != tmp->friends);

		tmp = tmp->next;

	} while (tmp != G);

	return grafo;

}

#endif

