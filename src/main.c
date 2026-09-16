#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "calc.h"
#include "vector_solutions.h"

/* function declarations */
void print_help(void);
int parse_file(char *filename);
void print_detail(SOLUTION *root_node);

/* definitions */
#define EXIT_OK    0
#define EXIT_ERROR 255
#define TRUE       1
#define FALSE      0
// solve
#define GREEDY     0
#define BEST       2

/* globals */
NODE *root_node;
int number_of_nodes;

/* program */
void print_detail(SOLUTION *root_node)
{
      SOLUTION *r_node;
      int counter;

      r_node = root_node;
      while(1){
            printf("Nodes with common color:");
            for(counter = 0;counter < number_of_nodes;counter++){
                  if(r_node->solution[counter] == 1){ printf(" %d",counter + 1); }
            }
            printf("\n");

            if(r_node->next == NULL){ break; }
            r_node = r_node->next;
      }

}

int parse_file(char *filename)
{
      FILE *fp;
      NODE *last_node;

      fp = fopen(filename,"r");
      if(fp == NULL){
            return FALSE;
      }
      fscanf(fp,"%d",&number_of_nodes);
      while(!feof(fp)){
            int from,to;

            from = 0;
            to = 0;
            fscanf(fp,"%d %d\n",&from,&to);
            if(root_node == NULL){
                  root_node = add_node(NULL,from,to);
            }else{
                  if(exists_in_list(from,to,root_node) == 0){
                        last_node = add_node(root_node,from,to);
                  }
            }
      }
      fclose(fp);

      return TRUE;
}

void print_help(void)
{
      printf("Graph Coloring problem solver by Vassileios Karakoidas (P/95053)\n");
      printf("usage: mapColoring.exe <data-file> [options]\n");
      printf("available options:\n\t-greedy\tdisplay solution greedy search (default)(fastest)\n");
      printf("\t-best\tdisplay best solution (brute force)(slowest)");
}

/* main functions */
int main(int argc, char *argv[])
{
      int solve_flag;

      root_node = NULL;
      if(argc < 2){
            print_help();
            return EXIT_OK;
      }
      printf("loading data ... ");
      if(parse_file(argv[1]) == FALSE){
            printf("Cannot find data file (%s)\n",argv[1]);
            return EXIT_ERROR;
      }
      printf("done\n");
      printf("Number of nodes: %d\n",number_of_nodes);
      if(init_problem(number_of_nodes,root_node) != 0){
            printf("Cannot initialize problem solver\n");
            return EXIT_ERROR;
      }
      solve_flag = GREEDY;
      if(argc == 3){
            if(strcmp(argv[2],"-greedy") == 0){ solve_flag = GREEDY; }
            if(strcmp(argv[2],"-best") == 0){ solve_flag = BEST; }
      }
      if(solve_flag == BEST){
            printf("Brute force selected\n");
            get_best_solution();
      }
      if(solve_flag == GREEDY){
            SOLUTION *solution;

            printf("Greedy selected\n");
            solution = get_solution();
            if(solution == NULL){
                  printf("Internal Error ... cannot solve problem\n");
                  return EXIT_ERROR;
            }
            printf("\n");
            printf("Number of colors: %d\n",count_nodes(solution));
            print_detail(solution);
      }
      free_list(root_node);

      return EXIT_OK;
}
