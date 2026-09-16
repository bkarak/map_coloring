#include "vector.h"
#include "vector_solutions.h"

#ifndef _CALC_H_
#define _CALC_H_

struct solution_int{
      int *solution;
      int no_colors;
};

typedef struct solution_int SOLUTION_INT;

void change_bool(int pos);
int init_problem(int number_of_nodes,NODE *root_node);
void print_node_array(void);
int calculate_function(NODE *root_node);
int solve(void);
double calculate_nodes(void);
void make_combinations(int counter);
void init_array(void);
void decide(void);
SOLUTION *get_solution(void);
void print_node_data(char *arr,int nodes);
/* full search */
void get_best_solution(void);
void recursive_solve(int counter,int *items,int item_size);
int *get_new_list(int first_item);
int *append_list(int *list,int size,int next_item);
char *blend_char(int *items,int item_no);
int is_solution(char *solution);
void print_best_detail(void);

#endif /* _CALC_H_ */
