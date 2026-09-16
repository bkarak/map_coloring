#ifndef _VECTOR_H_
#define _VECTOR_H_

/* type definitions */
struct node{
      int from;
      int to;
      struct node *next;
};

typedef struct node NODE;

/* function declarations */
NODE *create_node(int from,int to,NODE *next);
NODE *find_last_node(NODE *root_node);
NODE *add_node(NODE* root_node,int from,int to);
void print_node(NODE *node);
void print_list(NODE *root_node);
int compare_node(int from,int to,NODE *node);
int exists_in_list(int from,int to,NODE *root_node);
void free_list(NODE *root_node);

#endif /* _VECTOR_H_ */
