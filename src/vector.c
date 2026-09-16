#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

NODE *create_node(int from,int to,NODE *next)
{
      NODE *result;

      result = (NODE *)malloc(sizeof(NODE));
      result->from = from;
      result->to = to;
      result->next = next;

      return result;
}

NODE *find_last_node(NODE *root_node)
{
      NODE *result;

      result = root_node;
      while(1){
            if(result->next == NULL){ break; }
            result = result->next;
      }

      return result;
}

NODE *add_node(NODE* root_node,int from,int to)
{
      NODE *result,*cur_last;

      result = NULL;
      cur_last = NULL;
      if(root_node == NULL){
            return create_node(from,to,NULL);
      }
      cur_last = find_last_node(root_node);
      result = create_node(from,to,NULL);
      cur_last->next = result;

      return result;
}

void print_node(NODE *node)
{
      if(node->next == NULL){ printf("LAST_NODE -- :"); }
      if(node->next != NULL){ printf("NODE -- "); }
      printf("from: %d - to: %d\n",node->from,node->to);
}

void print_list(NODE *root_node)
{
      NODE *r_node;

      if(root_node == NULL){ printf("Empty list"); }
      r_node = root_node;
      while(1){
            print_node(r_node);
            if(r_node->next == NULL){ break; }
            r_node = r_node->next;
      }
}

int exists_in_list(int from,int to,NODE *root_node)
{
      NODE *r_node;

      r_node = root_node;
      while(1){
            if(compare_node(from,to,r_node) == 1){
                  return 1;
            }
            if(r_node->next == NULL){ return 0; }
            r_node = r_node->next;
      }
}

int compare_node(int from,int to,NODE *node)
{
      if((node->from == from) && (node->to == to)){
            return 1;
      }
      if((node->from == to) && (node->to == from)){
            return 1;
      }

      return 0;
}

void free_list(NODE *root_node)
{
      NODE *r_node,*tmp_node;

      r_node = root_node;
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




