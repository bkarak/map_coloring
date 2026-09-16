#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector_solutions.h"

SOLUTION *char_to_solution(char **char_sol,int no_nodes)
{
      SOLUTION *root_node,*tmp_solution;
      int counter;

      root_node = create_solution_no_copy(char_sol[0],NULL);
      tmp_solution = root_node;
      for(counter = 1;counter < no_nodes;counter++){
            tmp_solution = create_solution_no_copy(char_sol[counter],tmp_solution);
      }

      return root_node;
}

char **solution_to_char(SOLUTION *root_node)
{
      int co_nodes,counter;
      char **result;
      SOLUTION *r_node;

      co_nodes = count_nodes(root_node);
      result = (char **)malloc(sizeof(char *)*co_nodes);
      if(result == NULL){ return NULL; }
      r_node = root_node;
      for(counter = 0;counter < co_nodes;counter++){
            result[counter] = r_node->solution;
            if((r_node->next == NULL) && (counter != co_nodes - 1)){
                  printf("Warning!!!!! (solution_to_char)\n");
                  break;
            }
            r_node = r_node->next;
      }

      return result;
}

int count_nodes(SOLUTION *root_node)
{
      int result;
      SOLUTION *r_node;

      result = 0;
      r_node = root_node;
      while(1){
            result++;
            if(r_node->next == NULL){ break; }
            r_node = r_node->next;
      }

      return result;
}

char *blend(SOLUTION *root_sol,int size)
{
      char *result;
      int counter;
      SOLUTION *r_node;

      result = (char *)malloc(size*sizeof(char));
      if(result == NULL){ return NULL; }
      for(counter = 0;counter < size;counter++){
            result[counter] = 0;
      }
      r_node = root_sol;
      while(1){
            for(counter = 0;counter < size;counter++){
                  if(r_node->solution[counter] == 1){
                        result[counter] = 1;
                  }
            }
            if(r_node->next == NULL){ break; }
            r_node = r_node->next;
      }

      return result;
}

char *re_blend(char *solution,SOLUTION *new_node,int size)
{
      int counter;

      for(counter = 0;counter < size;counter++){
            if(new_node->solution[counter] == 1){
                  solution[counter] = 1;
            }
      }

      return solution;
}

int count(char *sol,int size)
{
      int counter,result;

      result = 0;
      for(counter = 0;counter < size;counter++){
            if(sol[counter] == 1){ result++; }
      }

      return result;
}

int is_overlap(char *solution,char *candidate,int size)
{
      int counter;

      for(counter = 0;counter < size;counter++){
            if((solution[counter] == 1) && (candidate[counter] == 1)){
                  return 1;
            }
      }

      return 0;
}

SOLUTION *find_max_matching(char *solution,SOLUTION *root_sol,int size)
{
      int max_size;
      SOLUTION *max_sol,*r_node;

      max_sol = NULL;
      max_size = 0;
      r_node = root_sol;
      while(1){
            if(is_overlap(solution,r_node->solution,size) == 0){
                  int c_size;

                  c_size = count(r_node->solution,size);
                  if((max_sol == NULL) || (max_size < c_size)){
                        max_size = c_size;
                        max_sol = r_node;
                  }
            }
            if(r_node->next == NULL){ break; }
            r_node = r_node->next;
      }

      return max_sol;
}

int is_perfect_match(SOLUTION *root_node,int size)
{
      char *lookup_table;
      int counter;

      lookup_table = NULL;
      lookup_table = blend(root_node,size);
      if(lookup_table == NULL){ return -1; }
      for(counter = 0;counter < size;counter++){
            if(lookup_table[counter] == 0){ return 0; }
      }

      return 1;
}

SOLUTION *find_max_solution(SOLUTION *root_sol,int size)
{
      SOLUTION *r_node,*result;
      int max_idx,max_nodes,counter,tmp_idx,tmp_nodes;

      r_node = root_sol;
      result = root_sol;
      max_idx = 0;
      max_nodes = 0;
      tmp_idx = 0;
      tmp_nodes = 0;
      while(1){
            for(counter = 0;counter < size;counter++){
                  if(r_node->solution[counter] == 1){ tmp_nodes++; }
            }
            if(tmp_nodes > max_nodes){
                  max_idx = tmp_idx;
                  max_nodes = tmp_nodes;
                  result = r_node;
            }
            tmp_idx++;
            tmp_nodes = 0;
            if(r_node->next == NULL){ break; }
            r_node = r_node->next;
      }

      return result;
}

void print_solution(SOLUTION *sol,int no_of_items)
{
      int counter;

      for(counter = 0;counter < no_of_items;counter++){
            printf("%d",sol->solution[counter]);
      }
      printf("\n");
}

void print_all_solution(SOLUTION *root_node,int no_of_items)
{
      SOLUTION *r_node;

      r_node = root_node;
      while(1){
            print_solution(r_node,no_of_items);
            if(r_node->next == NULL){
                  break;
            }
            r_node = r_node->next;
      }
}

SOLUTION *create_solution(char *sol,SOLUTION *previous,int no_of_items)
{
      SOLUTION *result;

      result = (SOLUTION *)malloc(sizeof(SOLUTION));
      if(result == NULL){ return NULL; }
      result->solution = copy_memory(sol,no_of_items);
      result->next = NULL;
      if(previous != NULL){ previous->next = result; }

      return result;
}

SOLUTION *create_solution_no_copy(char *sol,SOLUTION *previous)
{
      SOLUTION *result;

      result = (SOLUTION *)malloc(sizeof(SOLUTION));
      if(result == NULL){ return NULL; }
      result->solution = sol;
      result->next = NULL;
      if(previous != NULL){ previous->next = result; }

      return result;
}

SOLUTION *add_solution(char *sol,SOLUTION *last_node,int no_of_items)
{
      return create_solution(sol,last_node,no_of_items);
}

void free_solution(SOLUTION *root_node)
{
      SOLUTION *r_node,*tmp_node;

      r_node = r_node->next;
      while(1){
            if(r_node->next == NULL){
                  free(r_node);
                  break;
            }
            tmp_node = r_node->next;
            free(r_node);
            r_node = tmp_node;
            tmp_node = NULL;
      }
}

char *copy_memory(char *to_copy,int size)
{
      char *result;

      result = (char *)malloc(sizeof(char)*size);
      memcpy(result,to_copy,size);

      return result;
}

SOLUTION *copy_list(SOLUTION *root_node,int size)
{
      SOLUTION *new_root,*r_node,*n_node;

      new_root = create_solution(copy_memory(root_node->solution,size),NULL,size);
      if(new_root == NULL){ return NULL; }
      if(root_node->next == NULL){ return new_root; }
      r_node = root_node->next;
      n_node = new_root;
      while(1){
            n_node = create_solution(copy_memory(r_node->solution,size),n_node,size);
            if(r_node->next == NULL){ break; }
            r_node = r_node->next;
      }

      return new_root;
}

int compare_nodes(char *first,char *second,int size)
{
      int counter;

      for(counter = 0;counter < size;counter++){
            if(first[counter] != second[counter]){ return 0; }
      }

      return 1;
}

int delete_node(SOLUTION *root_node,SOLUTION *node,int size)
{
      SOLUTION *r_node,*previous;

      r_node = root_node;
      previous = NULL;
      while(1){
            if(compare_nodes(r_node->solution,node->solution,size) == 1){
                  if(previous != NULL){ previous->next = r_node->next; }
                  else{ root_node = r_node->next; }
                  free(r_node);
                  return 1;
            }
            if(r_node->next == NULL){ break; }
            previous = r_node;
            r_node = r_node->next;
      }

      return 0;
}
