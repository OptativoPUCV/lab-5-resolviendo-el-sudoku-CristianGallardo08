#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int aux[10];

    
    for(int i = 0 ; i < 9 ; i++){
        for(int k = 1; k <= 9 ; k++) aux[k]= 0;

        for(int j = 0 ; j < 9 ; j++){
            int valor = n->sudo[i][j];
            if(valor != 0){
                if(aux[valor]) return 0;
                aux[valor] = 1;
            }
        }
    }

    
    for(int j = 0 ; j < 9 ; j++){
        for(int k = 1; k <= 9 ; k++) aux[k] = 0;

        for(int i = 0 ; i < 9; i++){
            int valor = n->sudo[i][j];
            if(valor != 0){
                if(aux[valor]) return 0;
                aux[valor] = 1;
            }
        }
    }

    
    for(int k = 0; k < 9 ; k++){
        for(int i = 1; i <= 9; i++) aux[i] = 0;

        for(int p = 0; p < 9; p++){
            int fila = 3 * (k / 3) + (p / 3);
            int col  = 3 * (k % 3) + (p % 3);
            int valor = n->sudo[fila][col];

            if(valor != 0){
                if(aux[valor]) return 0;
                aux[valor] = 1;
            }
        }
    }
  return 1;
}

List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j,num = 0;
    for(i = 0;i < 9;i++){
      for(j = 0; j < 9; j++){
        if(n->sudo[i][j] == 0){
          num = 1;
          break;
        }
      }
      if(num)break;
    }
    if(!num){
      return list;
    }
    for(num = 1; num <= 9; num++){
      Node* nuevo = copy(n);
      nuevo->sudo[i][j] = num;

      if(is_valid(nuevo)){
        pushBack(list,nuevo);
      }

      else{
        free(nuevo);
      }

    }
    return list;
}


int is_final(Node* n){
    for(int i = 0 ; i< 9 ; i++){
      for(int j = 0;j < 9; j++){
        if(n->sudo[i][j] == 0){
          return 0;
        }
      }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S = createStack();
  push(S,initial);
  while(!is_empty(S)){
    Node * current = top(S);
    pop(S);
    (*cont) ++;

    if(is_final(current)){
      return current;

    }
    List *adj = get_adj_nodes(current);
    Node *nodoAdj = first(adj);
    while (nodoAdj)
    {
      push(S,nodoAdj);
      nodoAdj = next(adj);
    }
    free(current);
    
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/