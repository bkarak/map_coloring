#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "vector.h"
#include "vector_solutions.h"
#include "calc.h"

#define RECURSIVE

/* globals */
char *node_array;
int no_of_nodes;
NODE *root_list;
SOLUTION *v_solution,*v_last_solution;
/* full search */
char **solutions_list;
SOLUTION_INT min_solution;
int node_counter;

/* functions */
void print_node_data(char *arr,int nodes)
{
      int counter;

      for(counter = 0;counter < nodes;counter++){
            printf("%d",arr[counter]);
      }
      printf("\n");
}

double calculate_nodes(void)
{
      return pow((double)2,(double)no_of_nodes);
}

void print_node_array()
{
      print_node_data(node_array,no_of_nodes);
}

int calculate_function(NODE *root_node)
{
      NODE *r_node;
      int result,counter,sum;

      r_node = root_node;
      result =  1;
      sum = 0;
      for(counter = 0;counter < no_of_nodes;counter++){
            sum+=node_array[counter];
      }
      if(sum == 0){ return 0; }
      while(1){
            result = result && ((!node_array[r_node->from - 1]) || (!node_array[r_node->to - 1]));
            if(result == 0){ break; }
            if(r_node->next == NULL){ break; }
            r_node = r_node->next;
      }

      return result;
}

int solve(void)
{
      v_solution = NULL;
      v_last_solution = NULL;
      printf("Number of combinations: %0.f\n",calculate_nodes());
      printf("Solving problem ... please wait\n");
      make_combinations(0);

      return 1;
}

void make_combinations(int counter)
{
#ifndef RECURSIVE
      int inner;

      inner = 0;
      while(inner < no_of_nodes){
            for(inner = 0;inner < no_of_nodes && node_array[inner];inner++){
                  node_array[inner] = 0;
            }
            node_array[inner] = 1;
            decide();
      }
#else
      if((counter + 1) != no_of_nodes){
            make_combinations(counter + 1);
      }
      /* main body */
      decide();
      /* end of main body */
      change_bool(counter);
      if((counter + 1) != no_of_nodes){
            make_combinations(counter + 1);
      }
#endif
}

void change_bool(int pos)
{
      if(node_array[pos] == 0){
            node_array[pos] = 1;
      }else{
            node_array[pos] = 0;
      }
}

int init_problem(int number_of_nodes,NODE *root_node)
{
      no_of_nodes = number_of_nodes;
      root_list = root_node;
      node_array = (char *)malloc(sizeof(char)*no_of_nodes);
      if(node_array == NULL){
            printf("malloc failed ... exiting!\n");
            return 1;
      }
      init_array();
      if(solve() == 0){
            printf("Solve attempt failed ... exiting\n");
            return 1;
      }
      free(node_array);

      return 0;
}

void init_array(void)
{
      int counter;

      for(counter = 0;counter < no_of_nodes;counter++){
            node_array[counter] = 0;
      }
      node_array[0] = 1;
}

void decide(void)
{
      if(calculate_function(root_list) == 1){
            if(v_solution == NULL){
                  v_solution = add_solution(node_array,NULL,no_of_nodes);
                  v_last_solution = v_solution;
            }else{
                  v_last_solution = add_solution(node_array,v_last_solution,no_of_nodes);
            }
      }
}

/* greedy */
SOLUTION *get_solution(void)
{
      SOLUTION *max,*solution_node,*r_node,*root_node;
      char *blended;
      int answer;

      max = find_max_solution(v_solution,no_of_nodes);
      solution_node = add_solution(max->solution,NULL,no_of_nodes);
      root_node = solution_node;
      blended = blend(root_node,no_of_nodes);
      while(1){
            answer = is_perfect_match(root_node,no_of_nodes);
            if(answer == 1){ break; }
            if(answer == -1){
                  return NULL;
            }
            r_node = find_max_matching(blended,v_solution,no_of_nodes);
            if(r_node == NULL){
                  return NULL;
            }
            solution_node = add_solution(r_node->solution,solution_node,no_of_nodes);
            re_blend(blended,solution_node,no_of_nodes);
      }

      return root_node;
}

/* full search */
void get_best_solution(void)
{
      int counter,*tmp;

      node_counter = count_nodes(v_solution);
      solutions_list = solution_to_char(v_solution);
      min_solution.solution = NULL;
      min_solution.no_colors = INT_MAX;
      for(counter = 0;counter < node_counter;counter++){
            recursive_solve(counter,get_new_list(counter),1);
      }
      print_best_detail();
}

void recursive_solve(int counter,int *items,int item_size)
{
      int idx;
      char *blended;

      blended = blend_char(items,item_size);
      if(is_solution(blended) == 1){
            if(min_solution.no_colors > item_size){
                  min_solution.solution = items;
                  min_solution.no_colors = item_size;
            }
            return;
      }
      for(idx = counter + 1;idx < node_counter;idx++){
            if(is_overlap(blended,solutions_list[idx],no_of_nodes) == 0){
                  recursive_solve(idx,append_list(items,item_size,idx),item_size + 1);
            }
      }
}

int is_solution(char *sol)
{
      int counter;

      for(counter = 0;counter < no_of_nodes;counter++){
            if(sol[counter] != 1){ return 0; }
      }

      return 1;
}

char *blend_char(int *items,int item_no)
{
      char *result;
      int counter,inner;

      result = (char *)malloc(sizeof(char)*no_of_nodes);
      if(result == NULL){ return NULL; }
      for(counter = 0;counter < no_of_nodes;counter++){
            result[counter] = 0;
      }
      for(counter = 0;counter < item_no;counter++){
            for(inner = 0;inner < no_of_nodes;inner++){
                  if(solutions_list[items[counter]][inner] == 1){ result[inner] = 1; }
            }
      }

      return result;
}

int *get_new_list(int first_item)
{
      int *result;

      result = (int *)malloc(sizeof(int));
      if(result == NULL){ return NULL; }
      result[0] = first_item;

      return result;
}

int *append_list(int *list,int size,int next_item)
{
      int *result,counter;

      result = (int *)malloc(sizeof(int)*(size + 1));
      if(result == NULL){ return NULL; }
      for(counter = 0;counter < size;counter++){
            result[counter] = list[counter];
      }
      result[size] = next_item;

      return result;
}

void print_best_detail(void)
{
      int counter,inner;

      printf("Colors: %d\n\n",min_solution.no_colors);
      for(counter = 0;counter < min_solution.no_colors;counter++){
            printf("Nodes with common color: ");
            for(inner = 0;inner < no_of_nodes;inner++){
                  if(solutions_list[min_solution.solution[counter]][inner] == 1)
                        printf("%d ",inner + 1);
            }
            printf("\n");
      }
}
