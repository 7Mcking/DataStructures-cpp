//
//  main.cpp
//  linkedLists
//
//  Created by Naren Sadhwani on 28.06.23.
//

#include <iostream>
using namespace std;

class node{
public:
    int data;
    node *next;
};

void printList(node *a){
    while(a!=NULL){
        cout<< a->data<<endl;
        a=a->next;
    }
}


void push(node **head, int newdata){
    node *newnode = new node();
    newnode->data=newdata;
    newnode->next=(*head);
    
    (*head) = newnode;
}

void append(node **head, int newdata){
    
}

void insertAfter(node *prevnode, int newdata){
    
}

void deleteNode(node **head, int key){
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
    node *head = NULL;
    node *n1 = NULL;
    node *n2 = NULL;
    node *tail = NULL;
    head = new node();
    n1 = new node();
    n2 = new node();
    tail = new node();
    
    head->data = 2;
    head->next = n1;
    n1->data = 3;
    n1->next = n2;
    n2->data = 4;
    n2->next = tail;
    tail->data= 27;
    tail->next =NULL;
    
    printList(head);
    
}
