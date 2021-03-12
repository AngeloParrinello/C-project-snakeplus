CFLAG = -Wall -pedantic -Wno-comment -O3 -std=c89

all: ll_fgraph dl_fgraph cl_fgraph randgraph

ll_fgraph: ll_fgraph.h ll_fgraph.c ll_main.c
	gcc $(CFLAG) ll_fgraph.c ll_main.c -o ll_fgraph

dl_fgraph: dl_fgraph.h dl_fgraph.c dl_main.c
	gcc $(CFLAG) dl_fgraph.c dl_main.c -o dl_fgraph

cl_fgraph: cl_fgraph.h cl_fgraph.c cl_main.c
	gcc $(CFLAG) cl_fgraph.c cl_main.c -o cl_fgraph

randgraph: randgraph.c
	gcc $(CFLAG) randgraph.c -o randgraph

clean:
	rm -f ll_fgraph dl_fgraph cl_fgraph randgraph
