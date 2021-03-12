#ifdef LLIST 

struct list {
	unsigned int id;
	struct list *next;
};

struct fgraph {
	char *name;
	unsigned int id;
	struct list *friends;
	struct fgraph *next;
};

struct fgraph *copy_graph(struct fgraph *G);

int count_friendships(struct fgraph *G);

struct fgraph *read_fgraph(char *filename);
//static struct fgraph *fgraph_alloc(char *name, unsigned int id);
//static struct list *list_alloc(unsigned int id);
static int head_insert_individual(struct fgraph **G, char *name, unsigned int id);
static  int head_insert_list(struct list **L, unsigned int id);
static struct fgraph *search_individual(struct fgraph *G, unsigned int id);
static struct list *search_list(struct list *L, unsigned int id);
int insert_individual(struct fgraph **G, char *name, unsigned int id);
int insert_friendship(struct fgraph *G, unsigned int id1, unsigned int id2);
static int node_insert_list(struct list *L, unsigned int id);
static int node_insert_individual(struct fgraph *G, char *name, unsigned int id);


#endif
