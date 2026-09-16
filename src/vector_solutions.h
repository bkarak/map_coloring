#ifndef _VECTOR_SOLUTIONS_H_
#define _VECTOR_SOLUTIONS_H_

struct solution{
      char *solution;
      struct solution *next;
};

typedef struct solution SOLUTION;

char *copy_memory(char *to_copy,int size);
SOLUTION *create_solution(char *sol,SOLUTION *previous,int no_of_items);
SOLUTION *add_solution(char *sol,SOLUTION *last_node,int no_of_items);
void free_solution(SOLUTION *root_node);
void print_all_solution(SOLUTION *root_node,int no_of_items);
void print_solution(SOLUTION *sol,int no_of_items);
SOLUTION *find_max_solution(SOLUTION *root_sol,int size);
int is_perfect_match(SOLUTION *root_node,int size);
SOLUTION *find_max_matching(char *solution,SOLUTION *root_sol,int size);
char *blend(SOLUTION *root_sol,int size);
int count(char *sol,int size);
int is_overlap(char *solution,char *candidate,int size);
char *re_blend(char *solution,SOLUTION *new_node,int size);
SOLUTION *copy_list(SOLUTION *root_node,int size);
int delete_node(SOLUTION *root_node,SOLUTION *node,int size);
int compare_nodes(char *first,char *second,int size);
int count_nodes(SOLUTION *root_node);
char **solution_to_char(SOLUTION *root_node);
SOLUTION *char_to_solution(char **char_sol,int no_nodes);
SOLUTION *create_solution_no_copy(char *sol,SOLUTION *previous);

#endif /* _VECTOR_SOLUTIONS_H_ */
