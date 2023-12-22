A.cpp

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct link{

    char element;
    struct link *next;

}Link;

typedef struct{

    Link *head;
    Link *tail;
    Link *curr;
    int count;

}List;

Link *create_link(char it, Link *nextval){

    Link *n = (Link *) malloc(sizeof(Link));
    n->element = it; 
    n->next = nextval; 
    return n;
}

Link *create_link2(Link *nextval){

    Link *n = (Link *) malloc(sizeof(Link));
    n->next = nextval;
    return n;
}

List *create_list(){
    
    List *l = (List *) malloc(sizeof(List));
    l->curr = l->tail = l->head = create_link2(NULL);
    l->count = 0;
    return l;

}

void insert(List *l, char it){

    l->curr->next = create_link(it, l->curr->next);
    if(l->tail == l->curr) l->tail = l->curr->next;
    l->count++;
}

void moveToStart(List *l){
    l->curr = l->head;
}

void moveToEnd(List *l){
    l->curr = l->tail;
}

void next(List *l){
    if(l->curr != l->tail) l->curr = l->curr->next;
}

void printList(List *l){

    moveToStart(l);
    while(l->curr->next != NULL){
        printf("%c", l->curr->next->element);
        next(l);
    }
    printf("\n");

}

int main(){

    int i;
    string input;

    while(cin >> input){
        List *lista = create_list();
        for(i = 0; i < input.size(); i++){
            if(input[i] == '['){
                moveToStart(lista);
            }
            else if(input[i] == ']'){
                moveToEnd(lista);
            }
            else{
                insert(lista, input[i]);
                next(lista);
            }
        }
        printList(lista);
    }


    return 0;
}